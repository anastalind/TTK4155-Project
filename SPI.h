/** @package SPI.h
 *  Header-file for the SPI communication driver.
 *  @author: Anastasia Lindbäck and Marie Skatvedt
 */

#ifndef SPI_H
#define SPI_H

#include <stdint.h>

// Local headers
#include "bit_operations.h"

#define DDR_SPI DDRB
#define DD_MOSI DDB5
#define DD_MISO DDB6
#define DD_SCK DDB7

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
void SPI_write(char data);

#endif