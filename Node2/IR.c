/** @package IR.c
 *  c-file for the IR
 *  @authors: Anastasia Lindbäck and Marie Skatvedt
 */

#include "IR.h"


int goals;

/**
 * 
 */
void IR_init(void) {

    // Enable ADC
    set_bit(ADCSRA, ADEN);

    // Set reference to AVCC
    set_bit(ADMUX, REFS0);

    // Setting prescaler bits to 111 - division factor 128
    set_bit(ADCSRA, ADPS0);
    set_bit(ADCSRA, ADPS1);
    set_bit(ADCSRA, ADPS2);

    // Select ADC0 as analog channel
    clear_bit(ADMUX, MUX0);
    clear_bit(ADMUX, MUX1);
    clear_bit(ADMUX, MUX2);
    clear_bit(ADMUX, MUX3);
    clear_bit(ADMUX, MUX4);
    clear_bit(ADCSRB, MUX5);

 
    // Set ADC0 bit to configure as input pin
    set_bit(DDRF, ADC0);

    // Enable interrupt
    set_bit(ADCSRA, ADIE);

    // Clear interrupt flag
    clear_bit(ADCSRA, ADIF);

    // Resetting goals
    goals = 0;

}

/**
 * 
 */
uint16_t IR_read_photodiode(void) {
    // Start conversion by writing one to ADSC bit
    set_bit(ADCSRA, ADSC);

    // After the conversion is complete - ADIF is high - the conversion result can be foung in ADCL ADCH
    loop_until_bit_is_set(ADCSRA, ADIF);

    return ADC;
}

/**
 * 
 */ 
uint16_t IR_read_filtered_photodiode(void) {

    uint16_t sum;

    for (int i = 0; i < NUM_MEASUREMENTS; i++) {
        sum += IR_read_photodiode();
    }

    return (sum/NUM_MEASUREMENTS);
}


/**
 * 
 */
void count_goals(void) {
    if (IR_read_photodiode() == 1) {
        goals += 1;
    }
}


ISR(ADC_vect){

}

