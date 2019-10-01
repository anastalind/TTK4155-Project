/** @package menu.c
 * 
 *  @authors: Anastasia Lindbäck and Marie Skatvedt
 */

#include "menu.h"
#include "oled.h"
#include "joystick.h"

menu* current_menu = NULL; 

/**Function for creating new submenu and initialising it.
 * @param char* menu_title 
 * @param menu* parent_menu
 */
menu* menu_new(char* menu_title, menu* parent_menu){
    menu* new_menu = malloc(sizeof(menu));

    new_menu->title = menu_title;
    new_menu->parent = parent_menu;
    new_menu->child = NULL;
    new_menu->sibling = NULL;
}

/**Function for printing a submenu
 * 
 */
void menu_print(){
    OLED_print(current_menu->title);

    while (current_menu->sibling != NULL){
        OLED_go_to_line(current_line + 1);

        current_menu = current_menu->sibling;

        OLED_print(current_menu->title);
    }
}

/**Function for 
 * 
 */
void menu_navigate(){
    enum Direction direction = joystick_direction();

    switch(direction){
        case UP:
        case DOWN:
        case LEFT:
        case RIGHT:
    }
}