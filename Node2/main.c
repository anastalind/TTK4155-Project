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
#include "motor.h"
#include "solenoid.h"
#include "PLAY_GAME.h"
#include "PID.h"

#include <util/delay.h>
#include <avr/interrupt.h>


void main() {  

    sei();
    USART_init(9600);
    PWM_init();
    CAN_init();
    
    solenoid_init();
    motor_initialize();

    PID_init();

    while (1) {

        message msg = CAN_data_receive();
        //printf("MSG LENGTH %u \n\r", msg.length);
        //printf("SLIDER %u \n\r", msg.data[3]);

        // Controlling servo
        //double duty_cycle = PWM_joystick_to_duty_cycle(msg);
        //PWM_set_duty_cycle(duty_cycle);  

        // Pulse solenoid
        /*
        if (msg.data[2] == 1) {
            printf("Received msg about button press \n\r");
            control_solenoid();
        }
        */

        if (PID_FLAG == 1) {
            //PID_regulator();
            printf("%d\n\r",read_motor_encoder());
            motor_speed_controller(100);
            printf("%d\n\r",read_motor_encoder());
            PID_FLAG = 0;
        }


        
        //_delay_ms(1500);

        

        //printf("Get motor position %u \n\r", get_motor_position());


    
       
    

        //printf("\n\n");

    }
    
}


ISR(__vector_default)
{
    printf("Interrupt\n\r");

}