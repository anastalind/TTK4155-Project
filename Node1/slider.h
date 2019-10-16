/** @package slider.h
 *  
 *  Header-file considering the sliders on the USB-multiboards behaviour. 
 *  Converting the voltage resolution of 0-255 on the sliders to a percent-representation 0-100.
 *  
 *  @authors: Anastasia Lindbäck and Marie Skatvedt
 */

#ifndef SLIDER_H
#define SLIDER_H


#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <avr/io.h>
#include <util/delay.h>


/** Struct Sliders representing the left and right sliders respectively
 */
struct Sliders {
    int Left;
    int Right; 
};

/** Function retrieving position of right and left sliders as a percent-value 0-100
 *  @param void
 *  @return struct Sliders position - the position of the left and right slider.
 */
struct Sliders slider_position();

/** Test function for reading slider position.
 */    
void test_slider_position(void);
#endif 