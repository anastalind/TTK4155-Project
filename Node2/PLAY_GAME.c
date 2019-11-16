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
#include "motor.h"
#include "solenoid.h"
#include "PLAY_GAME.h"

#include <util/delay.h>
#include <avr/interrupt.h>


int GAME_OVER = 0;


/** Initialize necessary functions for playing the game.
 */
void play_game_initialize(void){
    sei();
    USART_init(9600);
    PWM_init();
    CAN_init();
    solenoid_init();
    motor_initialize();

}    

/** Function for playing the ping-pong game.
 */
void play_game(void){
    
    // Make global GAME_OVER

    // While not game over 
    while (!GAME_OVER) {

        int game_state = msg.data[5];

        switch (state) {
            // End game
            case 0: {
                // Send score
                break;
            }
            // Play game
            case 1: {
                // Play the game
                // if number of goals =3, set game over flag
                break;
            }
            // High score
            case 2: {
                break;
            }
            // Settings
            case 3: {
                break;
            }
            // Neutral
            case 4: {
                // Do nothing
                break;
            }
        }
    }

    

}

/** Function for ending the ping-pong game.
 */
void end_game(void){
    // End game, and retrieve high-scores?
}

