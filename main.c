#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>

#include "uart_driver.h"



void main() {

    UART_init(MYUBRR);

    while (1) {
        _delay_ms(5000);

        UART_trans('a');
        UART_recv();
    }
}
