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

    USART_init(9600);
    PWM_init();
    CAN_init();
    
    solenoid_init();
    motor_initialize();
    printf("\n\n");
    sei();

    while (1) {
        _delay_ms(20);

        message msg = CAN_data_receive();
        double duty_cycle = PWM_joystick_to_duty_cycle(msg);

        control_motor(msg);
        PWM_set_duty_cycle(duty_cycle);

        if (msg.data[2] == 1) {
            printf("Received msg about button press \n\r");
            control_solenoid();
        }
    }
}


ISR(INT2_vect)
{
    //printf("CAN INTERRUPT\n\r");

}