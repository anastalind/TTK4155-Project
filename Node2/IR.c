/** @package IR.c
 *  c-file for the IR
 *  @authors: Anastasia Lindbäck and Marie Skatvedt
 */

#include "IR.h"

#include <util/delay.h>

int goals;
int BALL_DETECTED_FLAG = 0;

/** Initialize Arduino shield for IR-communication.
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

/** Function for reading the signal from IR photodiode, detecting a goal.
 *  @return ADC - Analog turned digital signal from the photodiode.
 */
uint16_t IR_read_photodiode(void) {
    // Start conversion by writing one to ADSC bit
    set_bit(ADCSRA, ADSC);

    // After the conversion is complete - ADIF is high - the conversion result can be foung in ADCL ADCH
    loop_until_bit_is_set(ADCSRA, ADIF);

    return ADC;
}

/** Reading the digital filtered signal from the photodiode. 
 *  NUM_MEASUREMENTS = 4
 *  @return (sum/NUM_MEASUREMENTS) - The average value/filtered value of the photodiode signal.
 */ 
uint16_t IR_read_filtered_photodiode(void) {
    // Initialize the sum = 0 each time photodiode is read
    uint16_t sum = 0;

    // Sum 4 photodiode measurements
    for (int i = 0; i < NUM_MEASUREMENTS; i++) {
        sum += IR_read_photodiode();
    }
    // Return the average/filtered value
    return (sum/NUM_MEASUREMENTS);
}


/** Function for counting number of goals performed.
 *  @return goals - number of goals counted this round
 */
int counting_goals(void) {
    // The flag is checking whether the ball is registered or not
    if ((BALL_DETECTED_FLAG <= 2) && ((IR_read_filtered_photodiode() < GOAL_LIMIT))){
        BALL_DETECTED_FLAG += 1;
    }

    switch (BALL_DETECTED_FLAG){
        // If ball not yet detected, return goals
        case 0:
            return goals;
        // If ball detected once, increment goals by 1
        case 1:
            goals +=1;
            printf("GOAL! Score: %d \n\r",goals);
            return goals;
        // If ball is already detected and goal is incremented, return same goal count
        case 2:
            return goals;
        // If the ball is registered continously in the goal-area, the flag is cleared when the ball is no longer detected.
        default:
            if ((IR_read_filtered_photodiode() > GOAL_LIMIT)) {
                BALL_DETECTED_FLAG = 0;
                return goals;
            }
            else {
                return goals;
            }
    }
}

/** Test function for counting goals.
 */
void test_counting_goals(void){
    // So that printf can be used
    USART_init(9600);
    IR_init();

    while(1) {
        // Read filtered signal from photodiode
        // uint16_t IR_measurement = IR_read_filtered_photodiode();
        counting_goals();
        // printf("IR_measurement: %u \n\r", IR_measurement);
        _delay_ms(1);

    }
}


/** 
 * 
 
ISR(ADC_vect){

}

*/