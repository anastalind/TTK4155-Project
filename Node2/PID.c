/** @file PID.c
 *  @brief C-file for creating and using a PID-controller on the motor movement.
 *  @authors: Anastasia Lindbäck and Marie Skatvedt
 */

#include "PID.h"
#define F_CPU 16000000L
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "motor.h"
#include "bit_operations.h"
#include "CAN.h"
/*
int PID_FLAG = 0;

#define RESOLUTION 255
#define EDGE_SLACK 10
#define MAX_CONTROL_VAR_VALUE 150
*/

/*----Controller Gains-----*/
double K_p = 1;
double K_i = 0.03;
double K_d = 0.02;
double dt = 0.033;

int16_t position = 0;
int16_t error = 0;
int16_t prev_error = 0;
int16_t integral = 0;
int16_t derivative = 0;

int PID_FLAG = 0;


int16_t u = 0;

void PID_init()
{
	position = 0;
	error = 0;
	prev_error = 0;
	integral = 0;
	derivative = 0;
	
	cli();
	
	//Using normal mode
	set_bit(TCCR3B, CS31);

	//Enable timer interrupt
	set_bit(TIMSK3, TOIE3);
		
	sei();
	
	_delay_ms(200);
	
}



void PID_regulator()
{
	uint8_t ref = CAN_data_receive().data[3];
	//printf("REFERENCE VALUE %u \n\r", ref);

	
	if (ref < 10){
		ref = 10;
	}
	else if (ref > 245){
		ref = 245;
	}
	
	position = get_motor_position(); 

	error = ref - position;
	integral += error;
	
	if(error<7 && error > -7){
		integral = 0;
	}
	
	derivative = (error-prev_error);
	u = K_p*error + K_i*integral + K_d*derivative;

	prev_error = error;
	motor_speed_controller(u);

	
} 

ISR(TIMER3_OVF_vect)
{
	PID_FLAG = 1;
}

/** Function for initializing the PID-regulator.
 */
/*
void PID_init(double p_factor, double i_factor, double d_factor, PID *pid) {

	pid->sum_error = 0;
	pid->last_error = 0;

	pid->K_p = p_factor;
	pid->K_i = i_factor;
	pid->K_d = d_factor;

	cli();

	// Using normal mode
	set_bit(TCCR3B, CS31);

	// Enable timer interrupt
	set_bit(TIMSK3, TOIE3);

	sei();

	_delay_ms(500);

}
*/

/** Function for calculating control variable by using a PID regulator.
 * 	@param reference_value - The reference value from the current position
 * 	@param process_value - The value of the process position
 *  @param PID *pid - PID object pointer, setting the terms og P, I and D. 
 *  @return control_variable - Calculated control-variable.
 */
/*
int16_t PID_calculate_control_variable(uint8_t reference_value, uint8_t process_value, PID *pid){
	
	if (reference_value < EDGE_SLACK) {
		reference_value = EDGE_SLACK;
	}

	else if (reference_value > (RESOLUTION - EDGE_SLACK)){
		reference_value = RESOLUTION - EDGE_SLACK;
	}
	

	// Calulcating error
	int16_t error = reference_value - process_value;

	// Adding error to sum of errors which is used for the integral term in the control variable
	pid->sum_error += error;

	// Calculating the different terms in the control variable
	int16_t proportional = pid->K_p * error;
	int16_t integral = pid->K_i * pid->sum_error;
	int16_t derivative = pid->K_d * (error - pid->last_error);

	// 
	if (error < 7 && error > -7) {
		integral = 0;
	}

	// Calculating control variable using equation for discrete PID
	int16_t control_variable = proportional + integral + derivative;

	if (control_variable > MAX_CONTROL_VAR_VALUE) {
		control_variable = MAX_CONTROL_VAR_VALUE;
	}
	else if (control_variable < -MAX_CONTROL_VAR_VALUE) {
		control_variable = -MAX_CONTROL_VAR_VALUE;
	}

	// Update last error
	pid->last_error = error;
	//printf("\n\n");

	return ((int16_t)control_variable);
}
*/

/** Function for controlling the motor with PID regulator
 * @param message msg - CAN message from node 1 containing joystick position, button press, slider position and play game flag.
 */
/*
void PID_controller(message msg, PID *pid) {
    
    if (PID_FLAG == 1) {
        uint8_t reference_value = msg.data[3]; // Left slider value
		printf("REFERENCE VALUE %u \n\r", reference_value);

        uint8_t process_value = get_motor_position(); 
		//printf("PROCESS VALUE %u \n\r", process_value);

        int16_t control_variable = PID_calculate_control_variable(reference_value, process_value, pid);
		//printf("CONTROL VALUE %i \n\r", control_variable);

        motor_speed_controller(control_variable);

        PID_FLAG = 0;
    }
}
*/


/** Interrupt vector function.
 *  @param TIMER3_OVF_vect
 */
/*
ISR(TIMER3_OVF_vect) 
{

	PID_FLAG = 1;

}
*/
