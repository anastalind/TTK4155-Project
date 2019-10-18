/** @package USART.c
 *  c-file for the USART driver - to initialize, recieve and transfer data. 
 *  @authors: Anastasia Lindbäck and Marie Skatvedt
 */
#include "USART.h"


/** Function for initializing USART.
 *  @param unsigned int ubrr - UBRR register, User Baud Rate Register
 */
void USART_init (unsigned int bd) {
    // Check TXCn flag to check that transmitter has completed all transfers (BEFORE setting baud rate or frame format)
    //loop_until_bit_is_set(UCSR0A, TXC0);

    // Check RXC flag to check that there is no unread data in the receive buffer (BEFORE setting baud rate or frame format)
    //loop_until_bit_is_set(UCSR0A, RXC0);

    // Setting baud rate
    int ubrr = 0.15*((long)FOSC/((long)(16*bd))-1);

    UBRR0H = (unsigned char) (ubrr >> 8);
    UBRR0L = (unsigned char) (ubrr);

    // Setting frame format
    //UCSR0C = (1<<USBS0) || (3<<UCSZ00);

    // Enabling transmitter/receiver
    set_bit(UCSR0B, RXEN0);
    set_bit(UCSR0B, TXEN0);

    fdevopen(USART_trans, USART_recv);


    // If interrupt, clear Global Interrupt Flag
}

/** Function for recieving data from USART.
 *  @return UDR0 - Empty Handler, if register RXC0 (RX complete) is not set.
 */
unsigned char USART_recv (void) {
    // Wait for data to be received
    loop_until_bit_is_set(UCSR0A, RXC0);
    
    return UDRE0;
}

/** Function for transferring data from USART.
 *  @param unsigned char letter - Letter to be transferred 
 */
void USART_trans (unsigned char letter) {
    // Wait for empty transmit buffer
    loop_until_bit_is_set(UCSR0A, UDRE0);

    UDR0 = letter;
}

/** Function for testing USART.
 */
/*
void USART_test(void) {
    USART_init(9600);

    while (1) {
        USART_trans('a');

        char letter = USART_recv();
        letter -= 32;
        printf("Character received: %c \n\r", letter);

        _delay_ms(100);
    }
}
*/
