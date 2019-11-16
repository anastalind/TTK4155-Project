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
#include "PLAY_GAME.h"
#include "PID.h"

#include <util/delay.h>
#include <avr/interrupt.h>


void main() {  

    sei();
    USART_init(9600);
    PWM_init();
    CAN_init();
    
    solenoid_init();
    motor_initialize();

    PID_init();

    while (1) {

        message msg = CAN_data_receive();
        //printf("MSG LENGTH %u \n\r", msg.length);
        //printf("SLIDER %u \n\r", msg.data[3]);

        // Controlling servo
        //double duty_cycle = PWM_joystick_to_duty_cycle(msg);
        //PWM_set_duty_cycle(duty_cycle);  

        // Pulse solenoid
        if (msg.data[2] == 1) {
            printf("Received msg about button press \n\r");
            control_solenoid();
        }

        if (PID_FLAG == 1) {
            PID_regulator();
            PID_FLAG = 0;
        }

        // Controlling motor with PID regulator
        //PID_controller(msg, pid);

        //_delay_ms(1500);

        //motor_speed_controller(50);

        //printf("Get motor position %u \n\r", get_motor_position());


    /*
        // MENU - CONTROL FLAG
        // If play game is requested, play game
        if (msg.data[5] == 1) {
            printf("PLAY game is requested! \n\r");
            //play_game();
        } else if (msg.data[5] == 0) {
            printf("END game is requested! \n\r");
            //end_game();
        } else if (msg.data[5] == 2) {
            printf("HIGH SCORES are requested! \n\r");
            //show_highscore();
        }
    */

        //printf("\n\n");

    }
    
}


ISR(__vector_default)
{
    printf("Interrupt\n\r");

}