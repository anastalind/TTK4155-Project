/** @package menu.h
 * 
 *  @authors: Anastasia Lindbäck and Marie Skatvedt
 */

#ifndef MENU_H
#define MENU_H


#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <util/delay.h>

#include "joystick.h"
#include "OLED.h"

typedef struct {
    char* title;

    struct menu* parent;
    struct menu* child;
    struct menu* left_sibling;
    struct menu* right_sibling;
} menu;

menu* menu_new(char* menu_title, menu* parent_menu, menu* child_menu, menu* left_sibling_menu, menu* right_sibling_menu);

/**Function for printing a submenu
 * 
 */
void menu_print_submenu(menu* parent_menu, menu* current_menu);


/**Function for 
 * 
 */
menu* menu_navigate(menu* child_menu, direction dir);

menu* menu_init();

#endif