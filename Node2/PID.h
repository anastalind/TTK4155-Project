#ifndef PID_H
#define PID_H

#include "stdint.h"

#define SCALING_FACTOR 128

extern int PID_FLAG;

/**
 * 
 */ 
typedef struct {
	// Last process value
	int16_t last_error;
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

/** Maximum values
 *
 * Needed to avoid sign/overflow problems
 */
#define MAX_UINT UINT8_MAX
#define MAX_INT INT16_MAX
#define MAX_LONG INT32_MAX
#define MAX_I_TERM (MAX_LONG / 2)

// Boolean values
#define FALSE 0
#define TRUE 1

#endif
