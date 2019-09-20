#ifndef JOYSTICKSLIDER_DRIVER_H
#define JOYSTICKSLIDER_DRIVER_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define F_CPU 4915200

#include <avr/io.h>
#include <util/delay.h>

#define set_bit( reg, bit ) (reg |= (1 << bit))
#define clear_bit( reg, bit ) (reg &= ~(1 << bit))

#define ext_adc ((volatile char*) 0x1400)

struct Joystick {
    int x;
    int y; 
};

enum Direction {LEFT, RIGHT, UP, DOWN, NEUTRAL, UNKNOWN} Direction;

enum ADC_channel;


uint8_t select_channel(int channel);

// Returns the quadrant the joystick is positioned in by reading x- and y-position
int get_quadrant(struct Joystick position);

// Checking if direction is up or down (true) as opposed to right or left (false)
bool isUpDown(struct Joystick position);

//Get continous signal from x and y
struct Joystick joystick_position(void);

// Returns direction of joystick based on quadrant and 
enum Direction joystick_direction(void);


#endif