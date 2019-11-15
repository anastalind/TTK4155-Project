#include "PID.h"

int PID_FLAG = 0;

/**
 */
void PID_init(PID *pid)
{

	pid->sum_error = 0;
	pid->last_process_value = 0;

	pid->K_p = 0;
	pid->K_i = 0;
	pid->K_d = 0;

	cli();

	//Using normal mode
	set_bit(TCCR3B, CS31);

	//Enable timer interrupt
	set_bit(TIMSK3, TOIE3);

	sei();

	_delay_ms(500);
}

/**
 * 
 */
int16_t PID_controller(uint8_t reference_value, uint8_t process_value, PID *pid)
{
	int16_t error, control_variable, p_term, d_term;
	uint8_t i_term;

	error = reference_value - process_value;

	pid->sum_error += error;

	p_term = pid->K_p * error;
	i_term = pid->K_i * pid->sum_error;
	d_term = pid->K_d * (error - pid->last_error);

	pid->last_error = error;

	control_variable = (p_term + i_term + d_term);

	return ((int16_t)control_variable);
}

ISR(TIMER3_OVF_vect) {

	PID_FLAG = 1;

}