#include "joystickslider_driver.h"

uint8_t select_channel(ADC_channel channel){
    //Write the channel wanted from the ADC 
    ext_adc[0] = channel; 

    //Toggle write signal to activate channelchange
    set_bit(DDRD, DDD6);
    clear_bit(PORTD, PORTD6);
    set_bit(PORTD,PORTD6);

    //Delaying time t_c, waiting for writetoggle to be registered
    delay(40);

    // Returning 8 bit digital signal from ADC, converted from channel specified in input
    return ext_adc[0];
}

// Returns the quadrant the joystick is positioned in by reading x- and y-position
int get_quadrant(Joystick position) {
    if (position.x > 0 && position.y > 0) {
        return 1;
    }
    else if (position.x < 0 && position.y > 0) {
        return 2;
    }
    else if (position.x < 0 && position.y < 0) {
        return 3;
    }
    else if (position.x > 0 && position.y < 0) {
        return 4;
    }
}

// Checking if direction is up or down (true) as opposed to right or left (false)
bool isUpDown(Joystick position) {
    int abs_x = abs(position.x);
    int abs_y = abs(position.y);

    if (abs_y > abs_x) {
        return true;
    }
    else {
        return false;
    }
}

/*
//Get continous signal from sliders
float slider_position(void){


}
*/

//Get continous signal from x and y
Joystick joystick_position(void) {

    Joystick position;

    int resolution = 128;

    position.x = select_channel(5)/resolution;
    position.y = select_channel(4)/resolution;

    if (select_channel(5) < resolution) {
        position.x*(-1);
    } 

    if (select_channel(4) < resolution) {
        position.y*(-1);
    }
    return position;
}

// Returns direction of joystick based on quadrant and 
enum Joystick_direction joystick_direction(void){

    Joystick position = joystick_position();

    int quadrant = get_quadrant(position);
    bool isUpDown = isUpDown(position);

    switch(quadrant){
        case 1:
            if (isUpDown){
                return UP;
            }
            else {
                return RIGHT;
            }

        case 2:
            if (isUpDown){
                return UP;
            }
            else {
                return LEFT;
            }

        case 3:
            if (isUpDown) {
                return DOWN;
            }
            else {
                return LEFT;
            }

        case 4: 
            if (isUpDown){
                return DOWN;
            }
            else {
                return RIGHT;
            }

        default:
            return NEUTRAL;

    }

}


