#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/io.h>

#include "uart_driver.h"

#define F_CPU 4915200
#define set_bit( reg, bit ) (reg |= (1 << bit))
#define clear_bit( reg, bit ) (reg &= ~(1 << bit))


void main() {  

    /* EXERCISE 1
    UART_init(9600);

    while (1) {
        UART_trans('a');

        char letter = UART_recv();
        letter -= 32;
        printf("Character received: %c \n\r", letter);

        _delay_ms(100);
    }
    */
   
   set_bit(MCUCR, SRE);

   set_bit(DDRA, PORTA0);
   clear_bit(PORTA, PORTA0);

   set_bit(UCSR1A, UPE1);

}
