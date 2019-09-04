#include "uart_driver.h"
//#include <avr/io.h>

void UART_init (unsigned int ubrr) {
    const int BAUD = 0.15*((long)FOSC/((long)(16*ubrr))-1);

    UBRR0H = (unsigned char) (BAUD>>8);
    UBRR0L = (unsigned char) BAUD;

    UCSR0B = (1<<RXEN0) | (1<<TXEN0);

    UCSR0C = (1<<USBS0) | (1<<URSEL0) | (0<<UCSZ10) | (3<<UCSZ00);

    fdevopen(UART_trans, UART_recv);

}

unsigned char UART_recv (void) {
     if(!(UCSR0A & (1<<RXC0))){
        return 0;
    }

    return UDR0;
}

void UART_trans (unsigned char letter) {
    while (!(UCSR0A & (1 << UDRE0))){
    }

    UDR0 = letter;
}
