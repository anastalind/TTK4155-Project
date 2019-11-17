/** @file menu.c
 *  @brief C-file for the menu on the OLED - to move around in the menu.
 *  @authors: Anastasia Lindbäck and Marie Skatvedt
 */

#include "menu.h"


int PLAY_GAME_FLAG = 0;

/**Function for creating new submenu and initialising it.
 * @param char* menu_title - Title of the menu being created
 * @param menu* parent_menu - Pointer to struct menu that should be current menus' parent
 * @param menu* child_menu - Pointer to struct menu that should be current menus' child
 * @param menu* left_sibling_menu - Pointer to struct menu that should be current menus' left sibling
 * @param menu* right_sibling_menu - Pointer to struct menu that should be current menus' right sibling
 * @return new_menu - New menu struct with specified child, parent and siblings
 */
menu* menu_new(char* menu_title, menu* parent_menu, menu* child_menu, menu* left_sibling_menu, menu* right_sibling_menu){
    menu* new_menu = malloc(sizeof(menu));

    new_menu->title = menu_title;
    new_menu->parent = parent_menu;
    new_menu->child = child_menu;
    new_menu->left_sibling = left_sibling_menu;
    new_menu->right_sibling = right_sibling_menu;

    return new_menu;
}

/** Function for printing a submenu.
 *  @param menu* parent_menu - pointer to struct that is current menus' parent
 *  @param menu* current_menu - pointer to curren menu struct
 */
void menu_print_submenu(menu* parent_menu, menu* current_menu){
    OLED_reset();
    OLED_home();

    OLED_print(parent_menu->title);
    OLED_go_to_line(current_line + 2);

    menu* child_menu = parent_menu->child;

    while (child_menu != NULL){
        if (child_menu == current_menu) {
            OLED_print_highlight(child_menu->title, 5);
            OLED_go_to_line(current_line + 1);
        }
        
        else {
            OLED_print(child_menu->title);
            OLED_go_to_line(current_line + 1);
        }
        child_menu = child_menu->right_sibling;
    }

    // Print depending on the submenu chosen
    switch (PLAY_GAME_FLAG) {
        // End game
        case 0: {
            // Print the score on the screen for a while
            PLAY_GAME_FLAG = 4;
            // print ordinary screen
            break;
        }
        // Play game
        case 1: {
            // PLAYING GAME rolling over screen
            break;
        }
        // High score
        case 2: {
            // High score as main title
            break;
        }
        // Settings
        case 3: {
            // New menu with settings
            break;
        }
        // Neutral
        case 4: {
            //Back to ordinary
            break;
        }
    }
}



/** Function for navigating the menu by moving between siblings and parent/child. 
 *  @param menu* child_menu - Pointer to struct menu that corresponds to current menus' child
 *  @param direction dir - direction enum corresponding to joystick movement.
 *  @return current_menu - Menu struct that is chosen by joystick movement 
 */
menu* menu_navigate(menu* child_menu, direction dir){
    menu* current_menu = child_menu;

    if (dir == NEUTRAL) {
        current_menu = child_menu;
    }

    else if (dir == UP) {
        if (current_menu->left_sibling != NULL) {
            current_menu = current_menu->left_sibling;
        }
    }

    else if (dir == DOWN) {
        if (current_menu->right_sibling != NULL) {
            current_menu = current_menu->right_sibling; 
        }
    }

    else if (dir == LEFT) {
        if (current_menu->parent != NULL) {
            current_menu = current_menu->parent;
        }
    }
    else if (dir == RIGHT) {
        if (current_menu->child != NULL) {
            current_menu = current_menu->child;
        }
    }

    else {
        return current_menu;
    }
 
    // Navigate through abstraction layers by pressing joystick button 
    if (!(joystick_button_not_pressed())) {
        if (current_menu->title == "PLAY GAME"){
            current_menu = current_menu->child;
            PLAY_GAME_FLAG = 1;
            printf("PLAY GAME\n\r");

        } else if (current_menu->title == "END GAME"){
            // Return to main menu
            current_menu = (current_menu->parent)->parent;
            PLAY_GAME_FLAG = 0;
            printf("END GAME\n\r");

        } else if (current_menu->title == "HIGH SCORE"){
            current_menu = current_menu->child;
            PLAY_GAME_FLAG = 2;
            printf("HIGH SCORE\n\r");

        } else if (current_menu->title == "SETTINGS"){
            current_menu = current_menu->child;
            PLAY_GAME_FLAG = 3;
            printf("SETTINGS\n\r");

        } else if (current_menu->child != NULL){
            current_menu = current_menu->child;
        } 
    }
    return current_menu;
}

/** Function for creating main menu and submenus and setting their membervariables.
 *  @return main_menu - Menu struct corresponding to main menu. 
 */
menu* menu_init() {
    /* MAIN MENU */
    // Creating main menu, initializing its parent, child and siblings to NULL
    menu* main_menu = menu_new("MAIN MENU", NULL, NULL, NULL, NULL);

    /* SUBMENUS */
    // Submenu of main menu: setting left siblings and parent, right siblings and children must be set after initialization
    menu* play_game = menu_new("PLAY GAME", main_menu, NULL, NULL, NULL);
    menu* game_settings = menu_new("GAME SETTINGS", main_menu, NULL, play_game, NULL);
    menu* highscores = menu_new("HIGHSCORES", main_menu, NULL, game_settings, NULL);

    // GAME SETTINGS
    // Submenus of game settings
    menu* play_mode = menu_new("DIFFICULTY", game_settings, NULL, NULL, NULL);
    menu* players = menu_new("PLAYER MODE", game_settings, NULL, play_mode, NULL);

    // Submenus of players
    menu* single_player = menu_new("SINGLE PLAYER", players, NULL, NULL, NULL);
    menu* multi_player = menu_new("MULTIPLAYER", players, NULL, single_player, NULL);

    // PLAY GAME
    // Submenu of play game
    menu* end_game = menu_new("END GAME", play_game, NULL, NULL, NULL);

    // HIGH SCORE
    menu* high_score_submenu = menu_new("HIGH SCORE SUBMENU", highscores, NULL, NULL, NULL);

    /* SETTING THE CHILD VARIABLES*/
    // Setting child of main menu 
    main_menu->child = play_game;

    // Setting child of play game
    play_game->child = end_game;

    // Setting child of game settings
    game_settings->child = play_mode;

    // Setting child of players
    players->child = single_player;

    // Setting child of high score
    highscores->child = high_score_submenu;

    /* SETTING RIGHT SIBLINGS*/
    // Setting right siblings
    play_game->right_sibling = game_settings;
    game_settings->right_sibling = highscores;
    highscores->right_sibling = NULL;

    // Settings submenu
    play_mode->right_sibling = players;
    players->right_sibling = NULL;

    // Settings subsubmenu
    single_player->right_sibling = multi_player;
    multi_player->right_sibling = NULL;

    // Play game submenu
    end_game->right_sibling = NULL;

    // High score submenu
    high_score_submenu->right_sibling = NULL;

    return main_menu;
}

/** Test function 
 */
void menu_test(){
    OLED_init();

    menu* parent_menu = menu_init();
    menu* child_menu = parent_menu->child;
    menu* current_menu = NULL;

    joystick_calibrate();
    direction dir = joystick_direction();

    while (1) {
        current_menu = menu_navigate(child_menu, dir);
        
        menu_print_submenu(parent_menu, current_menu);
        _delay_ms(500);

        dir = joystick_direction();

        child_menu = current_menu;
        parent_menu = child_menu->parent;

    }
}

