/** @package oled.c
 * 
 *  @authors: Anastasia Lindbäck and Marie Skatvedt
 */

#include "oled.h"
#include "addresses.h"

/**Initialization routine, setting up OLED display
 * 
 */ 

void OLED_init(void){
    volatile char* address = cmnd_oled_addr;

    *address = (0xae); //Display off
    *address = (0xa1); //Segment remap
    *address = (0xda); //Common pads hardware: Alternative
    *address = (0x12);
    *address = (0xc8); //Common output scan direction: com63-com0
    *address = (0xa8); //Multiplex ration mode: 63
    *address = (0x3f); 
    *address = (0xd5); //Display divide ratio/freq. mode
    *address = (0x80); 
    *address = (0x81); //Contrast control
    *address = (0x50);
    *address = (0xd9); //Set pre-charge period
    *address = (0x21);
    *address = (0x20); //Set memory addressing mode to page addressing
    *address = (0x02);
    *address = (0xdb); //VCOM deselect level mode
    *address = (0x30);
    *address = (0xad); //Master configuration
    *address = (0x00);
    *address = (0xa4); //Out follow RAM content
    *address = (0xa6); //Set normal display
    *address = (0xaf); //Display on


}

/**Function for writing to OLED-screen
 * 
 */ 
void OLED_write(uint8_t data) {
    data_oled_addr[0] = data;
}

/**Function for controlling the OLEDs registers
 * 
 */ 
void OLED_command(uint8_t cmnd){
    cmnd_oled_addr[0] = cmnd;
}

/**Function for switching lines (0-7) on OLED
 * 
 */
void OLED_goto_line(int line) {
    OLED_command(oled_page_start_addr + line);
}

/**Function for clearing line (0-7) on OLED
 * 
 */ 
void OLED_clear_line(int line) {
    OLED_goto_line(line);

    for (int col = 0; col < OLED_COLS; col++) {
        OLED_write(0b00000000);
    }
    

}

/**
 * 
 */ 
void OLED_goto_column(int column) {
    OLED_command(oled_lower_col_addr + column);
}


void OLED_reset() {

}