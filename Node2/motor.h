/** @package motor.h
 *  Header-file for controlling the speed of the motor
 *  @authors: Anastasia Lindbäck and Marie Skatvedt
 */

#ifndef MOTOR_H
#define MOTOR_H

#include "bit_operations.h"

#include <avr/io.h>
#include <stdint.h>

/** Initializing motor by initializing TWI and enabling outputs and inputs from ATMega2560 (MJ1 and MJ2).
 */
void motor_initialize(void);

/** Resetting the motor encoder by toggling RST from MJ1.
 */
void reset_motor_encoder(void);

/** Function for reading the encoder counter.
 *  Reading motor encoder - Movement increases or decreases an internal 16 bits counter.
 */
void read_motor_eancoder(void);

void set_motor_speed(void);

void set_motor_direction(void);



#endif