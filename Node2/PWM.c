/** @package PWM.c
 *  c-file for the PWM 
 *  @authors: Anastasia Lindbäck and Marie Skatvedt
 */

#include "PWM.h"

void PWM_init(void) {
    // Set mode to Fast PWM (mode 14)
    set_bit(TCCR1A, WGM11);

    set_bit(TCCR1B, WGM12);
    set_bit(TCCR1B, WGM13);

    set_bit(TCCR1A, COM1A1);

    // Set clock frequency
    set_bit(TCCR1B, CS11);

    // Set pulse TOP and BOTTOM 
    // Top ?
    ICR1 = ;

    // Used as PWM output 
    // Output Compare Register
    OCR1A = 3000;

    // Timer interrupt
    set_bit(TIMSK1, OCIE1A);

    // Clearing interrupt flag
    TIFR1 = 0;

    // Set output servo pin 
}

void PWM_set_duty_cycle(int8_t position) {

}

void PWM_joystick_position_to_duty_cycle(message position) {
    int x_position = position.data[0];

    float PWM_resolution = 1.0; // From 1 ms to 2 ms
    float PWM_PW = 0.0;
    float PWM_D = 0.0;
    
    float ratio = 0.0;

    if (x_position < 0) {
        ratio = (x_position + 100)/100;
        PW = (PWM_resolution/2 * ratio) + 1;
    }

    else {
        ratio = x_position/100;
        PW = (PWM_resolution/2 * ratio) + 1.5;
    }

    // Calculating duty cycle
    PWM_D = PW/PWM_T;
}