/** @file SPI.h
 *  Header-file for the SPI communication driver.
 *  @author: Anastasia Lindbäck and Marie Skatvedt
 */

#ifndef SPI_H
#define SPI_H

#include <stdint.h>
#include <avr/io.h>

// Local headers
#include "bit_operations.h"

#define DDR_SPI DDRB
#define PIN_SS PB4
#define PIN_MOSI PB5
#define PIN_MISO PB6
#define PIN_SCK PB7

/**Function for initializing communication over SPI. 
 * 
 */ 
void SPI_init(void);

/**Function for configurating SPI as slave and reading the data register.
 * 
 */ 
char SPI_read(void);

/**Function for configurating SPI as master and transmitting data.
 * 
 */ 
uint8_t SPI_read_write(uint8_t data); 

void SPI_test(char data);

#endif