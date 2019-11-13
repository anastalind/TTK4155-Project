/** @package solenoid.h
 *  Header-file for the SPI communication driver.
 *  @author: Anastasia Lindbäck and Marie Skatvedt
 */

#ifndef SOLENOID_H
#define SOLENOID_H

#include "CAN.h"
#include "bit_operations.h"

#include <avr/io.h>
#include <stdbool.h>

void solenoid_init();

void control_solenoid();


#endif