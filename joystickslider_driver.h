#pragma once

#ifndef JOYSTICKSLIDER_DRIVER
#define JOYSTICKSLIDER_DRIVER

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

struct Joystick {
    int x = 0;
    int y = 0; 
};

enum Direction {LEFT, RIGHT, UP, DOWN, NEUTRAL, UNKNOWN};

enum ADC_channel {Y_axis = 4,
                  X_axis = 5,
                  R_slider = 6,
                  L_slider = 7};



uint8_t select_channel(ADC_channel channel){};

// Returns the quadrant the joystick is positioned in by reading x- and y-position
int get_quadrant(Joystick position) {};

// Checking if direction is up or down (true) as opposed to right or left (false)
bool isUpDown(Joystick position) {};

//Get continous signal from x and y
Joystick joystick_position(void) {};

// Returns direction of joystick based on quadrant and 
enum Joystick_direction joystick_direction(void){};


#endif