/** @package main.c
 * 
 *  main function for running the program - Controller. Node 1.
 * 
 *  @authors: Anastasia Lindbäck and Marie Skatvedt
 */


#include "UART.h"
#include "joystick.h"
#include "slider.h"
#include "ADC.h"
#include "sram_test.h"
#include "addresses.h"
#include "OLED.h"
#include "menu.h"
#include "SPI.h"
#include "CAN.h"

#include <util/delay.h>



void main() {  

    UART_init(9600);
    CAN_init();
    sei();

    //set_bit(UCSR1A, UPE1);
    set_bit(MCUCR, SRE); // Sets the SRE (Static Ram Enable) bit in the MCUCR (MCU Control Register) - enabling external write
    set_bit(SFIOR, XMM2); // Setting XMM2 (External Memory High Mask) bit in the SFIOR (Special Function IO Register) - use 4 bits for external memory address

    _delay_ms(1000);
    joystick_calibrate();
    joystick position = joystick_position();
    //bool button_press = is_button_pressed();
    
    while(1){
        position = joystick_position();
        //button_press = is_button_pressed();
        //printf("Is button pressed?? %i\n\r", button_press);

        //printf("Position x: %i\n\r", position.x);
        //printf("Position y: %i\n\r", position.y);
        joystick_CAN_transmit(position);
        _delay_ms(100);
    }

  
}
