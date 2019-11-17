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
#include "solenoid.h"
#include "PLAY_GAME.h"

#include "motor.h"
#include "PID.h"

#include <util/delay.h>
#include <avr/interrupt.h>


void main() {  

    sei();
    USART_init(9600);
    PWM_init();
    CAN_init();
    
    solenoid_init();

    motor_init();

    // Initialize PID-controller
    PID *pid;
    PID_init(pid);

    
    game_controller();
/*
    sei();
    USART_init(9600);
    PWM_init();
    CAN_init();
    
    solenoid_init();

    motor_init();

    PID *pid;
    PID_init(pid);

    while (1) {
        message msg = CAN_data_receive();

        for (int i = 0; i < msg.length; i++) {
            printf("MSG DATA %i: %u \n\r", i, msg.data[i]);
        }

        double duty_cycle = PWM_joystick_to_duty_cycle(msg);
        PWM_set_duty_cycle(duty_cycle);
        PID_controller(pid);

        printf("\n\n\r");
        
    }
   */ 
}


ISR(__vector_default)
{
    printf("Interrupt\n\r");

}