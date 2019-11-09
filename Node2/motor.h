/** @package motor.h
 *  Header-file for controlling the speed of the motor
 *  @authors: Anastasia Lindbäck and Marie Skatvedt
 */

#ifndef MOTOR_H
#define MOTOR_H

#include "bit_operations.h"
#include "PID.h"
#include "CAN.h"
#include "TWI_Master.h"

#include <avr/io.h>
#include <stdint.h>
#include <stdlib.h>
#include <util/delay.h>

typedef enum {LEFT, RIGHT, NEUTRAL} motor_direction;

/** Function for initializing motor by initializing TWI and enabling outputs and inputs from ATMega2560 (MJ1 and MJ2).
 */
void motor_initialize(void);


/** Function for resetting the motor encoder by toggling RST from MJ1.
 */
void reset_motor_encoder(void);


/** Function for reading the encoder counter.
 *  Reading motor encoder - Movement increases or decreases an internal 16 bits counter.
 */
void read_motor_encoder(void);


/** Function for setting the speed of the motor by sending the desired voltage to the motor box via TWI.
 *  @param uint8_t DAC_voltage - The desired voltage for the motor (0-5V)
 */
void set_motor_speed(uint8_t DAC_voltage);


/** Function for setting the direction of the motor by setting or clearing the DIR pin in MJ1 on motor box.
 *  @param motor_direction direction - Enum value that is either LEFT, RIGHT or NEUTRAL.
 */
void set_motor_direction(motor_direction direction);


/** Function for controlling the motor by joystick position.
 *  @param message position - CAN message containing joystick position of node 1.
 */
void control_motor(message position);
    
#endif