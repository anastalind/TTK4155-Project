/** @package SPI.c
 *  c-file for the SPI communication driver.
 *  @authors: Anastasia Lindbäck and Marie Skatvedt
 */

#include "SPI.h"

/**Function for initializing communication over SPI. 
 */
void SPI_init(void) {
    // Set MOSI
    set_bit(DDR_SPI, PIN_MOSI);

    // Set SCK output
    set_bit(DDR_SPI, PIN_SCK);

    // Set slave select
    set_bit(DDR_SPI, PIN_SS);
    
    // Enable Master
    set_bit(SPCR, MSTR);

    // Set clock rate fck/16
    set_bit(SPCR, SPR0);

    // Enable SPI
    set_bit(SPCR, SPE);
}

/**Function for configurating SPI as slave and reading the data register.
 * @return char SPDR - Data read from SPI
 */
char SPI_read(void) {
    // Write dummy byte
    SPI_write(0x00);

    /* Receiving data */
    // Wait for reception to complete
    loop_until_bit_is_set(SPSR, SPIF);

    // Return data
    return SPDR;
}

/**Function for configurating SPI as master and transmitting data.
 * @param char data - Data to send
 */
uint8_t SPI_write(uint8_t data) {
    clear_bit(DDR_SPI, PIN_SS);

    /* Transmission of data */
    // Start transmission
    SPDR = data;

    // Wait for transmission to complete
    loop_until_bit_is_set(SPSR, SPIF);

    set_bit(DDR_SPI, PIN_SS);

    return SPDR;
}


/**Function for testing SPI driver.
 * @param char data - Data to send
 */
void SPI_test(char data){
    SPI_init();

    while(1) {
        SPI_write(data);

    }
}