/** @file PID.h
 *  @brief Header-file for creating and using a PID-controller on the motor movement.
 *  @authors: Anastasia Lindbäck and Marie Skatvedt
 */

#ifndef PID_H
#define PID_H

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "bit_operations.h"

#define SCALING_FACTOR 128

// Global flag for the PID regulator
extern int PID_FLAG;

// Maximum values needed to avoid sign/overflow problems
#define MAX_UINT UINT8_MAX
#define MAX_INT INT16_MAX
#define MAX_LONG INT32_MAX
#define MAX_I_TERM (MAX_LONG / 2)

// Boolean values
#define FALSE 0
#define TRUE 1

typedef struct {
	// Last process value
	int16_t last_process_value;
	// Sum of errors, used for integration
	int32_t sum_error;
	// Proportional tuning constant
	uint8_t K_p;
	// Integral tuning constant
	uint8_t K_i;
	// Derivative tuning constant
	uint8_t K_d;
	// Maximum allowed error, avoid overflow
	int16_t max_error;
} PID;

/** Function for initializing the PID-regulator.
 */
void PID_init(PID *pid);

/** Introducing the PID-controller with each computation for P, I and D-terms.
 * 	@param reference_value - The reference value from the current position
 * 	@param process_value - The value of the process position
 *  @param PID *pid - PID object pointer, setting the terms og P, I and D. 
 *  @return control_variable - Calculated control-variable.
 */
int16_t PID_controller(uint8_t reference_value, uint8_t process_value, PID *pid);


#endif
