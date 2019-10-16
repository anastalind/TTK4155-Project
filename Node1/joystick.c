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

// Slack variable for neutral position of joystick
#define SLACK 2

// Resolution of joustick
#define RESOLUTION_START 0
#define RESOLUTION_END 255

// Origo of joystick area is approximately at (135,135) with a resolution scale 0-255 (some rightmost displacement, that is)
int resolution_left = 128;
int resolution_right = 128;

/** Function for returning the quadrant the joystick is position in by reading x-and y-position.
 *  @param struct Joystick position - Struct that yields the x- and y-values respectively.
 *  @return int 1-4 - Quadrant the joystick is in
 */
int get_quadrant(joystick position) {
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
bool is_vertical_direction(joystick position) {
    int abs_x = abs(position.x);
    int abs_y = abs(position.y);

    if (abs_y > abs_x) {
        return true;
    }
    else {
        return false;
    }
}

/** Function for detecting if joystiuck-button is pressed.
 *  @return 
 * 
 */
bool button_not_pressed(void) {
    bool joystick_button = (PINB & (1 << PINB2));
    return joystick_button;
} 


/** Function for calibrating the joystick neutral position (neutral = origo)
 */
void joystick_calibrate(void) {
    joystick position; 
    position.x = selected_channel_output(X_AXIS_CHANNEL);
    position.y = selected_channel_output(Y_AXIS_CHANNEL);

    resolution_left = position.x;
    resolution_right = RESOLUTION_END - position.x;
} 

/** Function converts digital signal from joysticks x- and y-values with voltage resolution 0-255 to percent-representation -100-100.
 *  @param void
 *  @return joystick position - Struct containing x-and-y-positions of joysticks represented as percentage of displacement -100-100.
 */
joystick joystick_position(void) {

    joystick position;

    // Converting from 0-255 resolution to -100-100 resolution in x-axis
    // Adding slack around origo on x-axis, so that neutral position will yield position (0,0)
    if ((selected_channel_output(X_AXIS_CHANNEL) >= (resolution_left)) && (selected_channel_output(X_AXIS_CHANNEL) <= (resolution_left))) {
        position.x = 0;
    }
    else if (selected_channel_output(X_AXIS_CHANNEL) < resolution_left) {
        position.x = -(((resolution_left-selected_channel_output(X_AXIS_CHANNEL))*100)/resolution_left);
    } 
    else {
        position.x = (((selected_channel_output(X_AXIS_CHANNEL)-resolution_left)*100)/resolution_right);
    }

    // Converting from 0-255 resolution to -100-100 resolution in y-axis
    // Adding slack around origo on y-axis, so that neutral position will yield position (0,0)
    if ((selected_channel_output(Y_AXIS_CHANNEL) >= (resolution_left)) && (selected_channel_output(Y_AXIS_CHANNEL) <= (resolution_left))) {
        position.y = 0;
    }
    
    else if (selected_channel_output(Y_AXIS_CHANNEL) < resolution_left) {
        position.y = -(((resolution_left-selected_channel_output(Y_AXIS_CHANNEL))*100)/resolution_left);
    } 

    else {
        position.y = (((selected_channel_output(Y_AXIS_CHANNEL)-resolution_left)*100)/resolution_right);
    }
    
    return position;
}

/** Function takes the direction and quadrant into consideration to decide in which direction the joystick is pointing (the most) towards. 
 *  @param void
 *  @return enum Direction - The direction, either UP, DOWN, LEFT or RIGHT
 */
direction joystick_direction(void){

    joystick position = joystick_position();

    printf("X-pos: %i\n\r", position.x);
    printf("Y-pos: %i\n\r", position.y);

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

/** Function for sending joystick position via CAN to Node 2. 
 *  @param joystick position - Position of joystick, struct containing x and y-positions (0-100%). 
 */
void joystick_CAN_transmit(joystick position) {
    message x_position;
    message y_position;
    // Give message struct position data for x and y respectively
    x_position.data[0] = position.x;
    y_position.data[0] = position.y;

    // Defining id for x and y 
    x_position.id = 1;
    y_position.id = 2; 

    // Defining length of data
    x_position.length = sizeof(position.x);
    y_position.length = sizeof(position.y);

    // Send position data from joystick as message struct via CAN to Node 2
    CAN_send_message(x_position);
    CAN_send_message(y_position);
    
}

/** Test function for reading joystick position.
 */
void test_read_joystick_position(void){
    //Read joystick-position: 
    _delay_ms(500);

    joystick joy_position = joystick_position();

    printf("X-value: %i\n\r", joy_position.x);
    printf("Y-value: %i\n\r", joy_position.y);
    printf("X-value: %i\n\r", selected_channel_output(5));
    printf("Y-value: %i\n\r", selected_channel_output(4));
}

