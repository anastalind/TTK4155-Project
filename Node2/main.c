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

#include <util/delay.h>


void main() {  

    // So we can use printf
    USART_init(9600);
    IR_init();
    PWM_init();

    while(1) {
        uint16_t IR_measurement = IR_read_photodiode();
        printf("IR_measurement: %u \n\r", IR_measurement);
        _delay_ms(100);

    }
/*

    CAN_init();


    while(1){
        message position = CAN_data_receive();
        double duty_cycle = PWM_joystick_to_duty_cycle(position);

        PWM_set_duty_cycle(duty_cycle);
        _delay_ms(100);
    }  
*/

     
}
