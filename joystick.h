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
#include <string.h>
#include <avr/io.h>
#include <util/delay.h>


/**Struct Joystick representing the x- an y-axis respectively
 */
struct Joystick {
    int x;
    int y; 
};

/**Enum Direction representing the directions of the joystick.
 */
enum Direction {LEFT, RIGHT, UP, DOWN, NEUTRAL, UNKNOWN} Direction;

/**ADC channels wanted represented as enum - x-axis, y-axis, right and left slider
 */
enum ADC_channel;

/** Function for returning the quadrant the joystick is position in by reading x-and y-position.
 *  @param struct Joystick position - Struct that yields the x- and y-values respectively.
 *  @return int 1-4 - Quadrant the joystick is in
 */
int get_quadrant(struct Joystick position);

/** Function checks whether the direction is up or down, as opposed to right or left.
 *  @param struct Joystick position - Struct that yields the x- and y-values respectively.
 *  @return true or false - up or down (true), right or left(false)
 */
bool is_vertical_direction(struct Joystick position);

/** Function converts digital signal from joysticks x- and y-values with voltage resolution 0-255 to percent-representation -100-100.
 *  @param void
 *  @return struct Joystick position - Struct containing x-and-y-positions of joysticks represented as percentage of displacement -100-100.
 */
struct Joystick joystick_position(void);

/** Function takes the direction and quadrant into consideration to decide in which direction the joystick is pointing (the most) towards. 
 *  @param void
 *  @return enum Direction - The direction, either UP, DOWN, LEFT or RIGHT
 */
enum Direction joystick_direction(void);

#endif