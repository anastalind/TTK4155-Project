/** @package main.c
 * 
 *  main function for running the program - Controller. Node 2. 
 * 
 *  @authors: Anastasia Lindbäck and Marie Skatvedt
 */


#include "USART.h"
#include "SPI.h"
#include "CAN.h"

#include <avr/interrupt.h>


void main() {  


    USART_init(9600);
    printf("Whatever\n\r");
    CAN_init();
    while(1){
        message position = CAN_data_receive();
        for (int i=0; i < position.length; i++){
            printf("Position: %u\n\r",position.data[i]);
            printf("Id: %u\n\r",position.id);
        }
    }
    
    
}


