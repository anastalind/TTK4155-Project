#include <stdlib.h>
#include <stdio.h>
#include <avr/io.h>

#include "uart_driver.h"
#include "sram_test.h"


#define F_CPU 4915200
#include <util/delay.h>

#define set_bit( reg, bit ) (reg |= (1 << bit))
#define clear_bit( reg, bit ) (reg &= ~(1 << bit))


void main() {  

    /* DAY 1
    UART_init(9600);

    while (1) {
        UART_trans('a');

        char letter = UART_recv();
        letter -= 32;
        printf("Character received: %c \n\r", letter);

        _delay_ms(100);
    }
    */
   
   

   /* DAY 2

    Checking if we are able to use the D latch by setting pin 0 and clearing pin 1
    Remember to set ALE signal (UPE1)

   set_bit(DDRA, DDA0);
   set_bit(DDRA, DDA1);

   set_bit(PORTA, PORTA0);
   clear_bit(PORTA, PORTA1);

   set_bit(UCSR1A, UPE1);

   while (1){};
   */
  UART_init(9600);

  // Setting the SRE and ALE signals
  printf("I have arrived at the main function\n\r");
  set_bit(MCUCR, SRE);
  set_bit(UCSR1A, UPE1);

  printf("I have set the SRE and ALE signals\n\r");
  // Setting the write signal to 0 (active low)
  set_bit(DDRD, DDD6);
  clear_bit(PORTD, PORTD6);

  // Setting the read signal to 0 (active low)
  set_bit(DDRD, DDD7);
  clear_bit(PORTD, PORTD7);

  printf("I will now perform the SRAM test\n\r");
  SRAM_test();

  //while (1){};
}
