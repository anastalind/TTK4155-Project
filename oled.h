/** @package oled.h
 * 
 *  @authors: Anastasia Lindbäck and Marie Skatvedt
 */

#ifndef OLED_H
#define OLED_H

#define OLED_LINES 8
#define OLED_COLS 128

#define FONT_OFFSET 32


#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>

uint8_t current_line;
uint8_t current_column;

/**Initialization routine, setting up OLED display
 */ 
void OLED_init(void);

/**Function for writing data to OLED-screen.
 */
void OLED_write(unsigned char character);

/** Function for printing data to OLED display.
 */
void OLED_print(char* data, ...);

/**Function for controlling the OLEDs registers.
 */ 
void OLED_command(uint8_t cmnd);

/**Function for switching lines (0-7) on OLED.
 */
void OLED_go_to_line(uint8_t line);

/**Function for switching columns (0-127) on OLED.
 */ 
void OLED_go_to_column(uint8_t column);

/**Function for switching position (line, column) on OLED.
 */ 
void OLED_position(uint8_t line, uint8_t column);

/**Function for clearing chosen line (0-7) on OLED.
 */ 
void OLED_clear_line(uint8_t line);

/**Function for resetting OLED, clearing all lines on OLED (clear display)
 */ 
void OLED_reset(void);

/**Function for returning OLED initial position in display matrix.
 */ 
void OLED_home(void);

#endif