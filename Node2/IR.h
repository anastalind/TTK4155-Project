/** @package IR.h
 *  Header file for the IR
 *  @authors: Anastasia Lindbäck and Marie Skatvedt
 */

#ifndef IR_H
#define IR_H

#include <avr/io.h>
#include <stdint.h>

#include "bit_operations.h"

#define ADC0 PF0

#define NUM_MEASUREMENTS 4

/**
 * 
 */
void IR_init(void);

/**
 * 
 */
uint16_t IR_read_photodiode(void);

/**
 * 
 */ 
uint16_t IR_read_filtered_photodiode(void);


/**
 * 
 */
void count_goals(void);

#endif