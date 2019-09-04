#ifndef UART_DRIVER_H
#define UART_DRIVER_H

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define FOSC 4915200 // Set the clock speed


void UART_init (unsigned int ubrr);

unsigned char UART_recv (void);

void UART_trans (unsigned char letter);

#endif
