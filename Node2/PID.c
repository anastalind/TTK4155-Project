#include "PID.h"

double p_factor = 1;
double i_factor = 0.03;
double d_factor = 0.02;

int PID_FLAG = 0;

#define ERROR_SLACK 15

void PID_init(PID* pid) {

    // Set tuning constants in pid
    pid->K_p = p_factor * SCALING_FACTOR;
    pid->K_i = i_factor * SCALING_FACTOR;
    pid->K_d = d_factor * SCALING_FACTOR;

    // Initializing error variables to zero from start
    pid->last_error = 0;
    pid->sum_errors = 0;

    // Initializing max error and max sum of errors as to limit error overflow and integral runaway
    pid->max_error = MAX_P_TERM/(pid->K_p + 1);
    pid->max_sum_errors = MAX_I_TERM/(pid->K_i + 1);

    cli();

    // Enabling timer 
	// Using normal mode
	set_bit(TCCR3B, CS31);

	// Enable timer interrupt
	set_bit(TIMSK3, TOIE3);

	sei();

	_delay_ms(500);

}

int16_t PID_calculate_control(uint8_t reference_value, uint8_t process_value, PID* pid) {

    int16_t p_term, i_term, d_term;
    int16_t error;
    int16_t control_variable;

    error = reference_value - process_value;

    printf("REFERENCE: %u \n\r", reference_value);
    printf("PROCESS: %u \n\r", process_value);
    printf("ERROR: %i \n\r", error);

    if (abs(error) > ERROR_SLACK) {
        pid->sum_errors += error;

    }

    //printf("SUM ERROR: %i \n\r", pid->sum_errors);

    // Calculate P term
    if (error > pid->max_error) {
        p_term = MAX_P_TERM;
    }

    else if(error < pid->max_error) {
        p_term = -MAX_P_TERM;
    }
    else {
        p_term = pid->K_p * error;
    }

    // Calculcate I term 
    int32_t temp = pid->sum_errors + error;

    if (temp > pid->max_sum_errors) {
        i_term = MAX_I_TERM;
        pid->sum_errors = pid->max_sum_errors;
    }

    else if (temp < pid->max_sum_errors) {
        i_term = -MAX_I_TERM;
        pid->sum_errors = -pid->max_sum_errors;
    }
    
    else {
        i_term = pid->K_i * pid->sum_errors;
        pid->sum_errors = temp;
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

    printf("CONTROL VARIABLE: %i \n\r", control_variable);

    return control_variable;

}

void PID_controller(PID* pid) {
    if (PID_FLAG == 1) {
        // Get reference and process values
        uint8_t reference_value = CAN_data_receive().data[3]; // Left slider (0 - 255)
        //printf("REFERENCE VALUE: %u \n\r", reference_value);

        uint8_t process_value = motor_position();
        //printf("PROCESS VALUE: %u \n\r", process_value);

        // Calculate the control variable
        int16_t control_value = PID_calculate_control(reference_value, process_value, pid);
        //printf("CONTROL VALUE: %u \n\r", control_value);

        // Apply control on system
        //motor_move(control_value);

    }
}

ISR(TIMER3_OVF_vect) {
    PID_FLAG = 1;
}