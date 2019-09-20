/** @package slider.c
 *  
 *  C-file considering the sliders on the USB-multiboards behaviour. 
 *  Converting the voltage resolution of 0-255 on the sliders to a percent-representation 0-100.
 *  
 *  @authors: Anastasia Lindbäck and Marie Skatvedt
 */


#include "slider.h"
#include "adc.h"


/** Function retrieving position of right and left sliders as a percent-value 0-100
 *  @param void
 *  @return struct Sliders position - the position of the left and right slider.
 */
struct Sliders slider_position(void){
    
    struct Sliders position;

    // Selecting which channel of the ADC to get output from. Hexadecimal representation of channel wanted from ADC.
    int left_slider = selected_channel_output(6);
    int right_slider = selected_channel_output(7);
    int resolution = 255;

    // Convert output with resolution 0-255 to percentage 0-100
    position.Left = (left_slider*100/resolution);
    position.Right = (right_slider*100/resolution);

    return position;
}

