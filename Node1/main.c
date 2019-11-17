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

ISR(__vector_default)
{
    printf("Interrupt\n\r");

}

void main() {  

    sei();
    UART_init(9600);
    CAN_init();

    //set_bit(UCSR1A, UPE1);
    set_bit(MCUCR, SRE); // Sets the SRE (Static Ram Enable) bit in the MCUCR (MCU Control Register) - enabling external write
    set_bit(SFIOR, XMM2); // Setting XMM2 (External Memory High Mask) bit in the SFIOR (Special Function IO Register) - use 4 bits for external memory address


    // USB MULTIBOARD INIT 
    _delay_ms(1000);
    joystick_calibrate();
    joystick position = joystick_position();
    Sliders slider = slider_position();
    
    // MENU INIT
    OLED_init();
    // Parent menu is Main Menu
    menu* parent_menu = menu_init();
    // Child menu is Play Game, which means that this is the first current menu from menu_navigate
    menu* child_menu = parent_menu->child;
    // Current menu is nothing
    menu* current_menu = NULL;
    // Direction of joystick
    direction dir = joystick_direction();

    while(1){

        menu_controller(parent_menu,child_menu,current_menu, dir);
        position = joystick_position();
        slider = slider_position();

        //printf("Slider left%i \n\r", slider.Left);
        //button_press = is_button_pressed();
        //printf("Is button pressed?? %i\n\r", button_press);

        //printf("Position x: %i\n\r", position.x);
        //printf("Position y: %i\n\r", position.y);
        
        game_controller_CAN_transmit(position, slider, PLAY_GAME_FLAG);

        _delay_ms(100);
    }
    
}
