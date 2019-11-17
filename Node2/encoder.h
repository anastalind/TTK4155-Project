#ifndef ENCODER_H
#define ENCODER_H

#define F_CPU 16000000

#include "bit_operations.h"

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>


void encoder_init(void);

void encoder_reset(void);

int16_t encoder_read(void);

#endif