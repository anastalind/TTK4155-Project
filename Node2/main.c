/** @package main.c
 * 
 *  main function for running the program - Controller. Node 2. 
 * 
 *  @authors: Anastasia Lindbäck and Marie Skatvedt
 */

#define F_CPU 16000000
#include "USART.h"
#include "SPI.h"
#include "CAN.h"
#include "PWM.h"
#include "IR.h"
#include "motor.h"
#include "solenoid.h"

#include <util/delay.h>
#include <avr/interrupt.h>


void main() {  

    sei();
    USART_init(9600);
    PWM_init();
    CAN_init();
    
    solenoid_init();
    motor_initialize();

    while (1) {
        //printf("Value read from motor encoder: %i\n\r", read_motor_encoder());
        message msg = CAN_data_receive();

        slider_controller_test(msg);
        //get_motor_position();

        double duty_cycle = PWM_joystick_to_duty_cycle(msg);

       // motor_speed_controller(msg);
        PWM_set_duty_cycle(duty_cycle);

        if (msg.data[2] == 1) {
            printf("Received msg about button press \n\r");
            control_solenoid();
        }
        printf("\n\n");


    }
    
}


ISR(__vector_default)
{
    //printf("Interrupt\n\r");

}