/** @package USART.h
 *  Header-file for the USART driver - to initialize, recieve and transfer data. 
 *  @author: Anastasia Lindbäck and Marie Skatvedt
 */
#ifndef USART_H
#define USART_H

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "bit_operations.h"

#define FOSC 4915200 // Set the clock speed

/** Function for initializing USART.
 *  @param unsigned int ubrr - UBRR register, User Baud Rate Register
 */
void USART_init (unsigned int ubrr);

/** Function for recieving data from USART.
 *  @return UDR0 - Empty Handler, if register RXC0 (RX complete) is not set.
 */
unsigned char USART_recv (void);

/** Function for transferring data from USART.
 *  @param unsigned char letter - Letter to be transferred 
 */
void USART_trans (unsigned char letter);

/** Function for testing USART.
 */
//void USART_test(void);

#endif
