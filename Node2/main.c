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
#include <util/delay.h>


void main() {  

    USART_init(9600);

    CAN_init();

    while(1){
        message position = CAN_data_receive();
        _delay_ms(100);
    }      
}
