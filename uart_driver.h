#include <avr/io.h>
#include <avr/interrupt.h>

#include "bit_operations.h"

#define FOSC 4915200 // Set the clock speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1


void UART_init (unsigned int ubrr) {};

unsigned char UART_recv (void){};

void UART_trans (unsigned char letter) {};
