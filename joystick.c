/** @package joystick.c
 * 
 *  C-file for the joystick on the USB-multiboards behaviour.
 *  Converting the voltage resolution of 0-255 on the y- and x-axis to a 
 *  percent-representation and deciding direction of joystick.
 * 
 *  @authors: Anastasia Lindbäck and Marie Skatvedt
 */

#include "joystick.h"

//ADC_channel with hexadecimal representation of channel wanted from ADC
#define X_AXIS_CHANNEL 5
#define Y_AXIS_CHANNEL 4

// Origo of joystick area is approximately at (135,135) with a resolution scale 0-255 (some rightmost displacement, that is)
#define RESOLUTION_LEFT 130
#define RESOLUTION_RIGHT 125

// Slack variable for neutral position of joystick
#define SLACK 7

/** Function for returning the quadrant the joystick is position in by reading x-and y-position.
 *  @param struct Joystick position - Struct that yields the x- and y-values respectively.
 *  @return int 1-4 - Quadrant the joystick is in
 */
int get_quadrant(struct Joystick position) {
    if (position.x < SLACK && position.x > -SLACK && position.y < SLACK && position.y > -SLACK) {
        return 0;
    }
    else if (position.x >= 0 && position.y > 0) {
        return 1;
    }
    else if (position.x < 0 && position.y >= 0) {
        return 2;
    }
    else if (position.x <= 0 && position.y < 0) {
        return 3;
    }
    else if (position.x > 0 && position.y <= 0) {
        return 4;
    }
    else {
        return 10000;
    }
}

/** Function checks whether the direction is up or down, as opposed to right or left.
 *  @param struct Joystick position - Struct that yields the x- and y-values respectively.
 *  @return true or false - up or down (true), right or left(false)
 */
bool is_vertical_direction(struct Joystick position) {
    int abs_x = abs(position.x);
    int abs_y = abs(position.y);

    if (abs_y > abs_x) {
        return true;
    }
    else {
        return false;
    }
}

/**
 * 
 */
bool is_not_button_pressed(void) {
    return (PINB & (1 << PINB2));
} 

/** Function converts digital signal from joysticks x- and y-values with voltage resolution 0-255 to percent-representation -100-100.
 *  @param void
 *  @return struct Joystick position - Struct containing x-and-y-positions of joysticks represented as percentage of displacement -100-100.
 */
struct Joystick joystick_position(void) {

    struct Joystick position;

    // Converting from 0-255 resolution to -100-100 resolution in x-axis
    // Adding slack around origo on x-axis, so that neutral position will yield position (0,0)
    if ((selected_channel_output(X_AXIS_CHANNEL) >= (RESOLUTION_LEFT)) && (selected_channel_output(X_AXIS_CHANNEL) <= (RESOLUTION_LEFT))) {
        position.x = 0;
    }
    else if (selected_channel_output(X_AXIS_CHANNEL) < RESOLUTION_LEFT) {
        position.x = -(((RESOLUTION_LEFT-selected_channel_output(X_AXIS_CHANNEL))*100)/RESOLUTION_LEFT);
    } 
    else {
        position.x = (((selected_channel_output(X_AXIS_CHANNEL)-RESOLUTION_LEFT)*100)/RESOLUTION_RIGHT);
    }

    // Converting from 0-255 resolution to -100-100 resolution in y-axis
    // Adding slack around origo on y-axis, so that neutral position will yield position (0,0)
    if ((selected_channel_output(Y_AXIS_CHANNEL) >= (RESOLUTION_LEFT)) && (selected_channel_output(Y_AXIS_CHANNEL) <= (RESOLUTION_LEFT))) {
        position.y = 0;
    }
    
    else if (selected_channel_output(Y_AXIS_CHANNEL) < RESOLUTION_LEFT) {
        position.y = -(((RESOLUTION_LEFT-selected_channel_output(Y_AXIS_CHANNEL))*100)/RESOLUTION_LEFT);
    } 

    else {
        position.y = (((selected_channel_output(Y_AXIS_CHANNEL)-RESOLUTION_LEFT)*100)/RESOLUTION_RIGHT);
    }
    
    return position;
}

/** Function takes the direction and quadrant into consideration to decide in which direction the joystick is pointing (the most) towards. 
 *  @param void
 *  @return enum Direction - The direction, either UP, DOWN, LEFT or RIGHT
 */
direction joystick_direction(void){

    struct Joystick position = joystick_position();

    int quadrant = get_quadrant(position);

    bool upDown = is_vertical_direction(position);

    switch(quadrant){
        case 0:
            return NEUTRAL;

        case 1:
            if (upDown){
                return UP;
            }
            else {
                return RIGHT;
            }

        case 2:
            if (upDown){
                return UP;
            }
            else {
                return LEFT;
            }

        case 3:
            if (upDown) {
                return DOWN;
            }
            else {
                return LEFT;
            }

        case 4: 
            if (upDown){
                return DOWN;
            }
            else {
                return RIGHT;
            }

        default:
            return UNKNOWN;

    }

}