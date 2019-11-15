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

#include <util/delay.h>
#include <avr/interrupt.h>

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
    // The while loop can run until the player looses (e.g. 3 goals)
    while (1) {
        // Read messages from CAN-bus
        message msg = CAN_data_receive();

        // Set duty cycle
        double duty_cycle = PWM_joystick_to_duty_cycle(msg);
        PWM_set_duty_cycle(duty_cycle);

        if (msg.data[2] == 1) {
            printf("Received msg about button press \n\r");
            control_solenoid();
        }

    }
}

/** Function for ending the ping-pong game.
 */
void end_game(void){
    // End game, and retrieve high-scores?
}