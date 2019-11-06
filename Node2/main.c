/** @package main.c
 * 
 *  main function for running the program - Controller. Node 2. 
 * 
 *  @authors: Anastasia Lindbäck and Marie Skatvedt
 */

#define F_CPU 16000000
#include "USART.h"
#include "SPI.h"
#include "CAN.h"
#include "PWM.h"
#include "IR.h"
#include "TWI_Master.h"
#include "motor.h"

#include <util/delay.h>


void main() {  

    test_joystick_to_servo();
    //test_counting_goals();



}


