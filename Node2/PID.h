#ifndef PID_H
#define PID_H

#include "CAN.h"
#include "motor.h"

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define SCALING_FACTOR 128

// Define max values
#define MAX_P_TERM INT16_MAX
#define MAX_I_TERM (INT32_MAX/2)
#define MAX_CONTROL_VALUE INT16_MAX

extern int PID_FLAG;

typedef struct {
    // Tuning variables, multiplied by SCALING_FACTOR
    int16_t K_p;
    int16_t K_i;
    int16_t K_d;

    int16_t last_error;
    int16_t max_error;
    int32_t sum_errors;
    int32_t max_sum_errors;
} PID;

void PID_init(PID* pid);

int16_t PID_calculate_control(uint8_t reference_value, uint8_t process_value, PID* pid);

void PID_controller(PID* pid);

#endif