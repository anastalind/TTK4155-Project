#include "joystickslider_driver.h"

enum ADC_channel {Y_axis = 4,
                  X_axis = 5,
                  R_slider = 6,
                  L_slider = 7};



uint8_t select_channel(int channel){
    //Write the channel wanted from the ADC 
    volatile char *address = ext_adc;

    address[0] = channel;

    //Delaying time t_c, waiting for writetoggle to be registered
    _delay_us(500);

    // Returning 8 bit digital signal from ADC, converted from channel specified in input
    return address[0];
}

// Returns the quadrant the joystick is positioned in by reading x- and y-position
int get_quadrant(struct Joystick position) {
    if (position.x >= 0 && position.y > 0) {
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

// Checking if direction is up or down (true) as opposed to right or left (false)
bool isUpDown(struct Joystick position) {
    int abs_x = abs(position.x);
    int abs_y = abs(position.y);

    if (abs_y > abs_x) {
        return true;
    }
    else {
        return false;
    }
}


//Get continous signal from sliders
int slider_position(int channel){
    int resolution = 255;
    int slider_value = select_channel(channel);
    int slider_percent_value = (slider_value*100/resolution);
    return slider_percent_value;
}

//Get continous signal from x and y
struct Joystick joystick_position(void) {

    struct Joystick position;

    int resolution_left = 135;
    int resolution_right = 120;

    // Converting from 0-255 resolution to -100-100 resolution in x-axis
    
    if ((select_channel(5) >= (resolution_left-1)) && (select_channel(5) <= (resolution_left+1))) {
        position.x = 0;
    }

    else if (select_channel(5) < resolution_left) {
        position.x = -(((resolution_left-select_channel(5))*100)/resolution_left);
    } 

    else {
        position.x = (((select_channel(5)-resolution_left)*100)/resolution_right);
    }

    // Converting from 0-255 resolution to -100-100 resolution in y-axis
    if ((select_channel(4) >= (resolution_left-1)) && (select_channel(4) <= (resolution_left+1))) {
        position.y = 0;
    }
    
    else if (select_channel(4) < resolution_left) {
        position.y = -(((resolution_left-select_channel(4))*100)/resolution_left);
    } 

    else {
        position.y = (((select_channel(4)-resolution_left)*100)/resolution_right);
    }
    
    return position;
}

// Returns direction of joystick based on quadrant and 
enum Direction joystick_direction(void){

    struct Joystick position = joystick_position();

    int quadrant = get_quadrant(position);

    bool upDown = isUpDown(position);

    switch(quadrant){
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
            return NEUTRAL;

    }

}