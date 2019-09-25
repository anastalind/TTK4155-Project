/** @package oled.h
 * 
 *  @authors: Anastasia Lindbäck and Marie Skatvedt
 */

#ifndef OLED_H
#define OLED_H

#define OLED_ROWS 8
#define OLED_COLS 128



void OLED_command(void);

void OLED_write(void);

void OLED_init(void);



#endif