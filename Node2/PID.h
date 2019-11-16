/** @file PID.h
 *  @brief Header-file for creating and using a PID-controller on the motor movement.
 *  @authors: Anastasia Lindbäck and Marie Skatvedt
 */


#ifndef PID_CONTROLLER_H_
#define PID_CONTROLLER_H_

extern int PID_FLAG;

/*Initializes the controller parameters and enables timer for controlling intervals.*/
void PID_init(void);

/*Regulates the motor position based on the encoder input and reference from the slider on the
 USB multifuntion board. Uses integral effect to reach correct position. */
void PID_regulator(void);

#endif /* PID_CONTROLLER_H_ */
/*
#ifndef PID_H
#define PID_H

#include <stdint.h>
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "bit_operations.h"
#include "CAN.h"
#include "motor.h"

// Global flag for the PID regulator
extern int PID_FLAG;

typedef struct {
	// Last error
	int16_t last_error;
	// Sum of errors, used for integration
	int32_t sum_error;
	// Proportional tuning constant
	double K_p;
	// Integral tuning constant
	double K_i;
	// Derivative tuning constant
	double K_d;
} PID;
*/
/** Function for initializing the PID-regulator.
 */
//void PID_init(double p_factor, double i_factor, double d_factor, PID *pid);

/** Introducing the PID-controller with each computation for P, I and D-terms.
 * 	@param reference_value - The reference value from the current position
 * 	@param process_value - The value of the process position
 *  @param PID *pid - PID object pointer, setting the terms og P, I and D. 
 *  @return control_variable - Calculated control-variable.
 */
//int16_t PID_calculate_control_variable(uint8_t reference_value, uint8_t process_value, PID *pid);

/** Function for controlling the motor with PID regulator
 * @param message msg - CAN message from node 1 containing joystick position, button press, slider position and play game flag.
 * @param PID *pid - pointer to a PID struct.
 */
//void PID_controller(message msg, PID *pid);

//#endif

