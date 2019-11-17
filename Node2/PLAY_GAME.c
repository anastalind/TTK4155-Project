/** @file PLAY_GAME.c
 *  @brief C-file for playing the Ping-Pong game.
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


/** Initialize necessary functions for playing the game.
 */
void play_game_initialize(void){
    sei();
    USART_init(9600);
    PWM_init();
    CAN_init();
    
    solenoid_init();

    motor_init();



}    

/** Function for playing the ping-pong game.
 */
void game_controller(void){
    message msg = CAN_data_receive();
    int game_state = msg.data[5];
   
    // Make global GAME_OVER
    while (1) { 
        msg = CAN_data_receive();
        printf("%d\n\r",game_state);
        switch (game_state) {
            // End game
            case 0: {
                
                end_game();
                game_state = msg.data[5];
                break;
            }

            // Play game
            case 1: {
                play_game();
                if (GAME_OVER) {
                    game_state = 0; 
                }
                else {
                    game_state = msg.data[5];
                }
                
                break;
            }

            // High score
            case 2: {
                game_state = msg.data[5];
                break;
            }

            // Settings
            case 3: {
                game_state = msg.data[5];
                break;
            }

        }
    }
}


/** Function for playing the ping-pong game. State = Playing.
 */
void play_game(void){


    GAME_OVER = 0; 

    // Check if ball miss
    curr_number_of_misses = counting_goals();

    // Have you reached game over
    if (curr_number_of_misses >= MAX_MISSES) {
        GAME_OVER = 1;
    }
    
    // Receive CAN-data
    message msg = CAN_data_receive();

    // Control servo based on joystick signal (x-axis)
    double duty_cycle = PWM_joystick_to_duty_cycle(msg);
    PWM_set_duty_cycle(duty_cycle);

    // Control the motor based on the left slider movement.
    PID_controller(pid, msg);

    // Punch solenoid when left button pressed.
    solenoid_control(msg);

}



/** Function for ending the ping-pong game. State = Game over. Neutral behaviour.
 */
void end_game(void){
    // Send score?
    reset_goals();
    // transmit not game over 

}

