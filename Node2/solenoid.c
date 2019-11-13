/** @package solenoid.c
 *  c-file 
 *  @authors: Anastasia Lindbäck and Marie Skatvedt
 */

#include "solenoid.h"

void solenoid_init() {
    set_bit(DDRB, PB4);
    set_bit(PORTB, PB4);
}

void control_solenoid() {
    clear_bit(PORTB, PB4);
    _delay_ms(500);
    set_bit(PORTB, PB4);   
}