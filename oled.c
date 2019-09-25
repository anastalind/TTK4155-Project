/** @package oled.c
 * 
 *  @authors: Anastasia Lindbäck and Marie Skatvedt
 */

#include "oled.h"
#include "addresses.h"
#include "fonts.h"

#include <avr/pgmspace.h>

/**Initialization routine, setting up OLED display
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
    *address = (0x20); //Set memory addressing mode
    *address = (0x00); // Horizontal mode

    *address = (0x21); // Set column address
    *address = (0x00);  // Set start address
    *address = (0x7f);  // Set end address

    *address = (0x22); // Set page address
    *address = (0x00); // Set start address
    *address = (0x07); // Set end address


    *address = (0xdb); //VCOM deselect level mode
    *address = (0x30);
    *address = (0xad); //Master configuration
    *address = (0x00);
    *address = (0xa4); //Out follow RAM content
    *address = (0xa6); //Set normal display
    *address = (0xaf); //Display on

    OLED_reset();
    OLED_home();

}

/**Function for writing data to OLED-screen.
 * @param unsigned char character - Character to be displayed on OLED-screen. Defined in fonts.h.
 */ 
void OLED_write(unsigned char character) {
    for (int line = 0; line < OLED_LINES; line++) {
        *data_oled_addr = pgm_read_byte(&font8[character-FONT_OFFSET][line]);
    }
}

/** Function for printing data to OLED display.
 */
void OLED_print(unsigned char character){

} 


/**Function for controlling the OLEDs registers.
 * @param uint8_t cmnd - Address for register in OLED.
 */ 
void OLED_command(uint8_t cmnd) {
    *cmnd_oled_addr = cmnd;
}

/**Function for switching lines (0-7) on OLED.
 * @param uint8_t line - Which line in OLED-matrix to go to.
 */
void OLED_go_to_line(uint8_t line) {
    OLED_command(oled_page_start_addr + line);
}


/**Function for switching columns (0-127) on OLED.
 * @param uint8_t column - Which column in OLED-matrix to go to.
 */ 
void OLED_go_to_column(uint8_t column) {
    OLED_command(oled_lower_col_addr + column);
}

/**Function for switching position (line, column) on OLED.
 */ 
void OLED_position(uint8_t line, uint8_t column) {
    OLED_go_to_line(line);
    OLED_go_to_column(column);
}

/**Function for clearing chosen line (0-7) on OLED.
 * @param int line - Which line to clear.
 */ 
void OLED_clear_line(int line) {
    OLED_go_to_line(line);

    for (int col = 0; col < OLED_COLS; col++) {
        OLED_write(' ');
    }
}

/**Function for resetting OLED, clearing all lines on OLED (clear display)
 */ 
void OLED_reset(void) {
    for (int line = 0; line < OLED_LINES; line++) {
        OLED_clear_line(line);
    }

}

/**Function for returning OLED initial position in display matrix.
 */ 
void OLED_home(void) {
    OLED_position(0,0);
}

/** Function for menu in OLED.
 */ 
void OLED_menu(void) {



}