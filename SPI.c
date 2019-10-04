/** @package SPI.c
 *  c-file for the SPI communication driver.
 *  @authors: Anastasia Lindbäck and Marie Skatvedt
 */

#include "SPI.h"

/**Function for initializing communication over SPI. 
 * 
 */
void SPI_init(void) {
    // Enable SPI
    set_bit(SPCR, SPE);

    // Enable SPI Interrupt
    set_bit(SPCR, SPIE);
}

/**Function for configurating SPI as slave and reading the data register.
 * 
 */
char SPI_read(void) {
    /* Initializing SPI as slave */
    // Set MISO output
    set_bit(DDR_SPI, DD_MISO);

    // Enable slave
    clear_bit(SPCR, MSTR); // USIKKER PÅ OM VI MÅ DET HER

    /* Receiving data */
    // Wait for reception to complete
    loop_until_bit_is_set(SPSR, SPIF);

    // Return data
    return SPDR;
}

/**Function for configurating SPI as master and transmitting data.
 * 
 */
void SPI_write(char data) {
    /* Initializing SPI as master */
    // Set MOSI output
    set_bit(DDR_SPI, DD_MOSI);

    // Set SCK output
    set_bit(DDR_SPI, DD_SCK);

    // Enable Master
    set_bit(SPCR, MSTR);

    // Set clock rate fck/16
    set_bit(SPCR, SPR0);

    /* Transmission of data */
    // Start transmission
    SPDR = data;

    // Wait for transmission to complete
    loop_until_bit_is_set(SPSR, SPIF);
}