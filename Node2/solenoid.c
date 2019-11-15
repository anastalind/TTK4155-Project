/** @file solenoid.c
 *  @brief c-file for controlling the solenoid.
 *  @authors: Anastasia Lindbäck and Marie Skatvedt
 */

#include "solenoid.h"

/** Function for initializing the solenoid by enabling pins.
 */
void solenoid_init() {
    set_bit(DDRB, PB4);
    set_bit(PORTB, PB4);
}

/** Function for toggling the solenoid pins and executing a pulse-movement.
 */
void control_solenoid() {
    clear_bit(PORTB, PB4);
    _delay_ms(300);
    set_bit(PORTB, PB4);   
}