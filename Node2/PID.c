#include "PID.h"

double p_factor = 1;
double i_factor = 0.03;
double d_factor = 0.02;

int PID_FLAG = 0;

#define ERROR_SLACK 15
#define EDGE_SLACK 10
#define MAX_RESOLUTION 255

void PID_init(PID* pid) {
    // Set tuning constants in pid
    pid->K_p = p_factor * SCALING_FACTOR;
    pid->K_i = i_factor * SCALING_FACTOR;
    pid->K_d = d_factor * SCALING_FACTOR;

    // Initializing error variables to zero from start
    PID_reset(pid);

    cli();

    // Enabling timer 
	// Using normal mode
	set_bit(TCCR3B, CS31);

	// Enable timer interrupt
	set_bit(TIMSK3, TOIE3);

	sei();

	_delay_ms(500);

}

void PID_reset (PID* pid) {
    pid->last_error = 0;
    pid->sum_errors = 0;
}

int16_t PID_calculate_control(uint8_t reference_value, uint8_t process_value, PID* pid) {

    int16_t p_term, i_term, d_term;
    int16_t error;
    int16_t control_variable;

    if (reference_value < EDGE_SLACK) {
        reference_value = EDGE_SLACK;
    }
    else if (reference_value > (MAX_RESOLUTION - EDGE_SLACK)) {
        reference_value = MAX_RESOLUTION - EDGE_SLACK;
    }

    error = reference_value - process_value;

    // Calculate P term
    p_term = pid->K_p * error;

    // Calculcate I term 
    if (abs(error) > ERROR_SLACK) {
        pid->sum_errors += error;
        i_term = pid->K_i * pid->sum_errors;
    }
    else {
        i_term = 0;
    }
    
    // Calculate D term
    d_term = pid->K_d * (error - pid->last_error);

    // Calculate control variable
    control_variable = (p_term + i_term + d_term)/SCALING_FACTOR;

    if (control_variable > MAX_CONTROL_VALUE) {
        control_variable = MAX_CONTROL_VALUE;
    }

    else if (control_variable < -MAX_CONTROL_VALUE) {
        control_variable = -MAX_CONTROL_VALUE;

    }

    return control_variable;

}

void PID_controller(PID* pid, message msg) {
    if (PID_FLAG == 1) {
        // Get reference and process values
        uint8_t reference_value = msg.data[3]; // Left slider (0 - 255)
        //printf("REFERENCE VALUE: %u \n\r", reference_value);

        uint8_t process_value = motor_position();
        //printf("PROCESS VALUE: %u \n\r", process_value);

        // Calculate the control variable
        int16_t control_value = PID_calculate_control(reference_value, process_value, pid);
        //printf("CONTROL VALUE: %i \n\r", control_value);

        // Apply control on system
        motor_move(control_value);

    }
}

ISR(TIMER3_OVF_vect) {
    PID_FLAG = 1;
}