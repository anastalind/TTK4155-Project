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
//#include "TWI_Master.h"
#include "motor.h"

#include <util/delay.h>
#include <avr/interrupt.h>


ISR(__vector_default){
    printf("DEFAULT ISR\n\r");
}

void main() {  
    cli();
    //test_joystick_to_servo();
    
    //test_counting_goals();

    USART_init(9600);
    PWM_init();
    CAN_init();
    motor_initialize();
    printf("\n\n\n\n\n\n\n\n");
    sei();

    //test_joystick_to_servo();
    while (1) {

        message position = CAN_data_receive();
        control_motor(position);

        //_delay_ms(500);
    }

}


