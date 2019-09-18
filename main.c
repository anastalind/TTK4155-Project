/** @package main.c
 *  main function for running the program.
 */
#include <stdlib.h>
#include <stdio.h>
#include <avr/io.h>

#include "uart_driver.h"
#include "joystickslider_driver.h"
#include "sram_test.h"

#define F_CPU 4915200
#include <util/delay.h>

#define set_bit( reg, bit ) (reg |= (1 << bit))
#define clear_bit( reg, bit ) (reg &= ~(1 << bit))

#define ext_adc (volatile char *) 0x1400


void main() {  

/* 
DAY 1: INITIAL ASSEMBLY OF MICROCONTROLLER AND RS-232
    
    UART_init(9600);

    while (1) {
        UART_trans('a');

        char letter = UART_recv();
        letter -= 32;
        printf("Character received: %c \n\r", letter);

        _delay_ms(100);
    }
*/

/* 
DAY 2: ADDRESS DECODING AND EXTERNAL RAM
*/
    UART_init(9600);
    
    //Checking if we are able to use the D latch by setting pin 0 and clearing pin 1
    //Remember to set ALE signal (UPE1)
    /*
    set_bit(DDRA, DDA0);
    set_bit(DDRA, DDA1);

    set_bit(PORTA, PORTA0);
    clear_bit(PORTA, PORTA1);

    set_bit(UCSR1A, UPE1);

    // Setting the SRE and ALE signals
    */
    set_bit(MCUCR, SRE);
    set_bit(SFIOR, XMM2);
    SRAM_test();
    /*
    set_bit(UCSR1A, UPE1);
    printf("SRE and ALE signals are set\n\r");
    
    // Setting the write signal to 0 (active low)
    set_bit(DDRD, DDD6);
    clear_bit(PORTD, PORTD6);

    // Setting the read signal to 0 (active low)
    set_bit(DDRD, DDD7);
    clear_bit(PORTD, PORTD7);
    */
    // Testing the GAL IC

    // Setting addresses for RAM, ADC and OLED
    volatile char *ext_ram = (char *) 0x1800;
    //volatile char *ext_adc = (char *) 0x1400;
    volatile char *ext_oled = (char *) 0x1000;



    
    //uint8_t some_value = rand();
    while (1){
    // Selecting RAM (pin 19)
    //ext_ram[0] = some_value;

    // Selecting ADC (pin 18)
    //ext_adc[0] = rand();

    // Selecting OLED (pin 17)
    //ext_oled[0] = rand();  

        joystick_position();
        
        
    };
    
}