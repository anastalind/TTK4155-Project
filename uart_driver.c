#include "uart_driver.h"
void UART_init (unsigned int ubrr) {
    UBRR0H = (unsigned char) (ubrr>>8);
    UBRR0L = (unsigned char) (ubrr);

    UCSR0B = (1<<RXEN0) | (1<<TXEN0);

    UCSR0C = (1<<URSEL0)|(1<<USBS0)|(3<<UCSZ00); // Set frame format: 8 bit data, 2 stop bit

}

unsigned char UART_recv (void) {
    loop_until_bit_is_set(UCSR0A, RXC0);
    return UDRE0;
}

void UART_trans (unsigned char letter) {
    UDRE0 = letter;
    loop_until_bit_is_set(UCSR0A, TXC0);
}
