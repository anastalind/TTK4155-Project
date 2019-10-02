/** @package main.c
 * 
 *  main function for running the program - Controller.
 * 
 *  @authors: Anastasia Lindbäck and Marie Skatvedt
 */


#include "uart_driver.h"
#include "joystick.h"
#include "slider.h"
#include "adc.h"
#include "sram_test.h"
#include "addresses.h"
#include "oled.h"
#include "menu.h"


//#include <stdlib.h>
//#include <stdio.h>
//#include <avr/io.h>
//#define F_CPU 4915200
//#include <util/delay.h>
//#define set_bit( reg, bit ) (reg |= (1 << bit))
//#define clear_bit( reg, bit ) (reg &= ~(1 << bit))




void main() {  

    UART_init(9600);


    //set_bit(UCSR1A, UPE1);

    set_bit(MCUCR, SRE); // Sets the SRE (Static Ram Enable) bit in the MCUCR (MCU Control Register) - enabling external write
    set_bit(SFIOR, XMM2); // Setting XMM2 (External Memory High Mask) bit in the SFIOR (Special Function IO Register) - use 4 bits for external memory address
    //SRAM_test();
    _delay_ms(1000);
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

    //uint8_t some_value = rand();
    
    //volatile char* oled_data_channel = (char* ) 0x1200;

    
    OLED_init();

    menu* parent_menu = menu_init();

    menu* child_menu = parent_menu->child;

    menu* current_menu = NULL;

    direction dir = joystick_direction();

    int button_press = !(is_not_button_pressed());


    while (1) {
        current_menu = menu_navigate(child_menu, dir);

        menu_print_submenu(parent_menu, current_menu);

        //_delay_ms(500);

        dir = joystick_direction();

        child_menu = current_menu;

        parent_menu = child_menu->parent;

        printf("LEFT = 0, RIGHT, UP, DOWN, NEUTRAL, UNKNOWN\n\r");
        printf("Direction: %i\n\r", dir);

    }
        
    // Selecting RAM (pin 19)
    //ext_ram[0] = some_value;

    // Selecting ADC (pin 18)
    //ext_adc[0] = rand();

    // Selecting OLED (pin 17)
    //ext_oled[0] = rand();  


//DAY 3: A/D converting and joystick input
    
        //Read joystick-posisition: 
/*
        _delay_ms(500);

        struct Joystick joy_position = joystick_position();

        printf("X-value: %i\n\r", joy_position.x);
        printf("Y-value: %i\n\r", joy_position.y);
        printf("X-value: %i\n\r", selected_channel_output(5));
        printf("Y-value: %i\n\r", selected_channel_output(4));


        //Read Slider position: 

        struct Sliders position = slider_position();

        printf("Left-slider: %i\n\r", position.Left);
        printf("Right-slider: %i\n\r", position.Right);
*/

//DAY 4:    
  
}
