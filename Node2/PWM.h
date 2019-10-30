/** @package PWM.h
 *  Header file for the PWM 
 *  @authors: Anastasia Lindbäck and Marie Skatvedt
 */

#ifndef PWM_H
#define PWM_H

#include <avr/io.h>
#include <stdint.h>

#include "CAN.h"
#include "bit_operations.h"

#define PWM_T 20

// Set pulse TOP and BOTTOM
// Prescaler divider, chosen when setting clock frequency
#define N 8

// Frequency of PWM signal, calculated based on period (T = 20 ms) => f = 1/T = 50 Hz
#define F_PWM 50


#define MAX_DEFLECTION_ANGLE_LEFT 0.900
#define MAX_DEFLECTION_ANGLE_RIGHT 2.100

// Clock frequency
#define F_CLK 16000000

// Setting TOP using equation given in datasheet
//uint32_t TOP = (F_CLK/(N * F_PWM)) - 1;

/**
 * 
 */ 
void PWM_init(void);

/**
 * 
 */
double PWM_joystick_to_duty_cycle(message position);


/**
 * 
 */
void PWM_set_duty_cycle(double duty_cycle);

#endif