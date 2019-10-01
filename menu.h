/** @package menu.h
 * 
 *  @authors: Anastasia Lindbäck and Marie Skatvedt
 */

#ifndef MENU_H
#define MENU_H


#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>

typedef struct {
    char* title;

    struct menu* parent;
    struct menu* child;
    struct menu* sibling;
} menu;


#endif