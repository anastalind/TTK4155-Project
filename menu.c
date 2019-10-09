/** @package menu.c
 * 
 *  @authors: Anastasia Lindbäck and Marie Skatvedt
 */

#include "menu.h"

/**Function for creating new submenu and initialising it.
 * @param char* menu_title 
 * @param menu* parent_menu
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

/**Function for printing a submenu
 * 
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
}


/**Function for 
 * 
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

    if (!(is_not_button_pressed())) {
        if (current_menu->child != NULL) {
            current_menu = current_menu->child;
        }
    }
    return current_menu;
}


menu* menu_init() {
    /* MAIN MENU */
    // Creating main menu, initializing its parent, child and siblings to NULL
    menu* main_menu = menu_new("MAIN MENU", NULL, NULL, NULL, NULL);

    /* SUBMENUS */
    // Submenu of main menu: setting left siblings and parent, right siblings and children must be set after initialization
    menu* play_game = menu_new("PLAY GAME", main_menu, NULL, NULL, NULL);
    menu* end_game = menu_new("END GAME", main_menu, NULL, play_game, NULL);
    menu* game_settings = menu_new("GAME SETTINGS", main_menu, NULL, end_game, NULL);
    menu* highscores = menu_new("HIGHSCORES", main_menu, NULL, game_settings, NULL);

    // Submenus of game settings
    menu* play_mode = menu_new("DIFFICULTY", game_settings, NULL, NULL, NULL);
    menu* players = menu_new("PLAYER MODE", game_settings, NULL, play_mode, NULL);

    // Submenus of players
    menu* single_player = menu_new("SINGLE PLAYER", players, NULL, NULL, NULL);
    menu* multi_player = menu_new("MULTIPLAYER", players, NULL, single_player, NULL);

    /* SETTING THE CHILD VARIABLES*/
    // Setting child of main menu
    main_menu->child = play_game;

    // Setting child of game settings
    game_settings->child = play_mode;

    // Setting child of players
    players->child = single_player;

    /* SETTING RIGHT SIBLINGS*/
    // Setting right siblings
    play_game->right_sibling = end_game;
    end_game->right_sibling = game_settings;
    game_settings->right_sibling = highscores;
    highscores->right_sibling = NULL;

    play_mode->right_sibling = players;
    players->right_sibling = NULL;

    single_player->right_sibling = multi_player;
    multi_player->right_sibling = NULL;

    return main_menu;
}

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