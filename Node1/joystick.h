/** @package joystick.h
 *  
 *  Header-file considering the joystick on the USB-multiboards behaviour. 
 *  Converting the voltage resolution of 0-255 on the y- and x-axis to a 
 *  percent-representation and deciding direction of joystick.
 *  
 *  @authors: Anastasia Lindbäck and Marie Skatvedt
 */

#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avr/io.h>
#include <util/delay.h>

#include "ADC.h"
#include "CAN.h"


/** Struct Joystick representing the x- an y-axis respectively
 */
typedef struct {
    int x;
    int y; 
} joystick;

/** Enum Direction representing the directions of the joystick.
 */
typedef enum {LEFT, RIGHT, UP, DOWN, NEUTRAL, UNKNOWN} direction;

/**ADC channels wanted represented as enum - x-axis, y-axis, right and left slider
 */
enum ADC_channel;

// Button flag
extern int BUTTON_PRESSED_FLAG;

/** Function for returning the quadrant the joystick is position in by reading x-and y-position.
 *  @param struct Joystick position - Struct that yields the x- and y-values respectively.
 *  @return int 1-4 - Quadrant the joystick is in
 */
int get_quadrant(joystick position);

/** Function checks whether the direction is up or down, as opposed to right or left.
 *  @param struct Joystick position - Struct that yields the x- and y-values respectively.
 *  @return true or false - up or down (true), right or left(false)
 */
bool is_vertical_direction(joystick position);

/**
 * 
 */ 
bool joystick_button_not_pressed(void);

/**Function for calibrating joystick at start.
 * 
 */
void joystick_calibrate(void);

/** Function converts digital signal from joysticks x- and y-values with voltage resolution 0-255 to percent-representation -100-100.
 *  @param void
 *  @return struct Joystick position - Struct containing x-and-y-positions of joysticks represented as percentage of displacement -100-100.
 */
joystick joystick_position(void);

/** Function takes the direction and quadrant into consideration to decide in which direction the joystick is pointing (the most) towards. 
 *  @param void
 *  @return enum Direction - The direction, either UP, DOWN, LEFT or RIGHT
 */
direction joystick_direction(void);
/** Test function for reading joystick position.
 */ 
void test_read_joystick_position(void);

bool is_button_pressed();

void game_controller_CAN_transmit(joystick position);
   


#endif