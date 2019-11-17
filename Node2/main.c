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

int GAME_OVER = 0;
int curr_number_of_misses = 0;

void main() {  

    sei();
    USART_init(9600);
    PWM_init();
    CAN_init();
    
    solenoid_init();

    motor_init();

/*
    // Initialize PID-controller
    PID *pid;
    PID_init(pid);

    message msg = CAN_data_receive();
    int game_state = msg.data[5];

    while (1) {
        msg = CAN_data_receive();

        if (game_state == 1) {
            printf("GAME STATE: %i \n\r", game_state);
            GAME_OVER = 0; 

            // Check if ball miss
            curr_number_of_misses = counting_goals();

            // Have you reached game over
            if (curr_number_of_misses >= MAX_MISSES) {
                GAME_OVER = 1;
                game_state = 0;
            }

            else {
                // Control servo based on joystick signal (x-axis)
                double duty_cycle = PWM_joystick_to_duty_cycle(msg);
                PWM_set_duty_cycle(duty_cycle);

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
            printf("Got nothing \n\r");
            game_state = msg.data[5];
        }

*/
}
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