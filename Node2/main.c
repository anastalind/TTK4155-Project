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


#define MAX_MISSES 3 


void main() {  

    sei();
    USART_init(9600);
    PWM_init();
    CAN_init();

    IR_init();
    
    solenoid_init();

    motor_init();

    PID *pid;
    PID_init(pid);

    //printf("PID PARAMETERS: %i %i %i \n\r", pid->K_p, pid->K_i, pid->K_d);

    int curr_number_of_misses = 0;

    message msg = CAN_data_receive();
    uint8_t game_state = msg.data[5];
    uint8_t position = motor_position();

    while (1) {

        message msg = CAN_data_receive();

        position = motor_position();

        for (int i = 0; i < msg.length; i++) {
            //printf("MSG.DATA %d: %u \n\r", i, msg.data[i]);
        }

        if (game_state == 1) {
            // Check if ball miss
            curr_number_of_misses = counting_goals();
            // Have you reached game over
            if (curr_number_of_misses >= MAX_MISSES) {
                //printf("GAME OVER");
                game_state = 0;
                CAN_transmit_game_info(1);
                reset_goals();
                _delay_ms(5000);
                CAN_transmit_game_info(0);

            }
    
            else {
                // Control servo based on joystick signal (x-axis)
                double duty_cycle = PWM_joystick_to_duty_cycle(msg);
                PWM_set_duty_cycle(duty_cycle);
                //printf("DUTY CYCLE: %lf \n\r", duty_cycle);

                // Control the motor based on the left slider movement.
                PID_controller(pid, msg);

                // Punch solenoid when left button pressed.
                solenoid_control(msg);
                game_state = msg.data[5];
            }

        }
    

        else if (game_state == 0) {
            reset_goals();
            PID_reset(pid);
            game_state = msg.data[5];
            
        }
        
        else {
            game_state = msg.data[5];
        }
    }
}



    
/*

    while (1) {
        message msg = CAN_data_receive();
        position = motor_position();
        
        for (int i = 0; i < msg.length; i++) {
            printf("MSG.DATA %i: %u \n\r",i,  msg.data[i]);
        }
        
       printf("MSG LENGTH %u \n\r", msg.length);


        if (game_state == 1) {

            GAME_OVER_FLAG = 0; 

            // Check if ball miss
            curr_number_of_misses = counting_goals();
            //printf("CURRENT NUM OF MISSES: %i \n\r", curr_number_of_misses);

            // Have you reached game over
            if (curr_number_of_misses >= MAX_MISSES) {
                GAME_OVER_FLAG = 1;
                game_state = 0;
            }

            else {
                // Control servo based on joystick signal (x-axis)
                double duty_cycle = PWM_joystick_to_duty_cycle(msg);
                PWM_set_duty_cycle(duty_cycle);
                //printf("DUTY CYCLE: %lf \n\r", duty_cycle);

                // Control the motor based on the left slider movement.
                PID_controller(pid, msg);

                // Punch solenoid when left button pressed.
                solenoid_control(msg);
                game_state = msg.data[5];
            }

        }

        else if (game_state == 0) {
            reset_goals();
            PID_reset(pid);
            game_state = msg.data[5];
        }

        else {
            //printf("Got nothing \n\r");
            game_state = msg.data[5];
        } 
    }
}
*/
/* EXERCISE 8 - PID, SERVO and SOLENOID */
/*
    while (1) {
        message msg = CAN_data_receive();

        //solenoid_control(msg);

        if (msg.data[2] == 1) {
            clear_bit(PORTB, PB4);
            _delay_ms(300);
            set_bit(PORTB, PB4);
        }

        //printf("SOLENOID BOOL: %u \n\r", msg.data[2]);

        double duty_cycle = PWM_joystick_to_duty_cycle(msg);
        PWM_set_duty_cycle(duty_cycle);
        PID_controller(pid, msg);  
    }
*/


