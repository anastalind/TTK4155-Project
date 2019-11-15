/** @file joystick.c
 * 
 *  @brief C-file for the joystick on the USB-multiboards behaviour.
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

int BUTTON_PRESSED_FLAG = 0;

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
 *  @return joystick_button - Returns if joystick button is pressed.
 */
int joystick_button_not_pressed(void) {
    int joystick_button = (PINB & (1 << PINB2));
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


/** Function for telling if touch-button is pressed.
*/
bool is_button_pressed() {
    return ((PINB & (1 << PINB0)) || (PINB & (1 << PINB1)));
}

/** Function for sending joystick position, buttons, slider positions and play-game flag via CAN to Node 2. 
 *  @param joystick position - Position of joystick, struct containing x and y-positions.
 *  @param Sliders slider_position - position of slider right and left.
 *  @param PLAY_GAME_FLAG - Flag set when play game is selected in the main menu.
 */
void game_controller_CAN_transmit(joystick position, Sliders slider_position, int PLAY_GAME_FLAG) {
    message msg;
    msg.length = 6;
    msg.id = 0;

    msg.data[0] = position.x;
    msg.data[1] = position.y;
    msg.data[3] = slider_position.Left;
    msg.data[4] = slider_position.Right;
    msg.data[5] = PLAY_GAME_FLAG;

    //printf("Slider %i \n\r", msg.data[3]);

    // The flag is checking whether the button is registered or not
    if ((BUTTON_PRESSED_FLAG <= 1) && (is_button_pressed())){
        BUTTON_PRESSED_FLAG += 1;
    }
    switch (BUTTON_PRESSED_FLAG){
        // If button press not detected
        case 0:
            msg.data[2] = 0;
            break;
        // If button pressed detected
        case 1:
            //Send button pressed
            msg.data[2] = 1;
            break; 
            //printf("Send button pressed.\n\r");


        // If the button is registered continously, the flag is cleared when the ball is no longer detected.
        default:
            if (!is_button_pressed()) {
                BUTTON_PRESSED_FLAG = 0;
                msg.data[2] = 0;
            } else {
                msg.data[2] = 0;
            }
            break;
    }

    CAN_send_message(msg);  
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

