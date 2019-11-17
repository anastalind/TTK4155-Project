#ifndef MOTOR_H
#define MOTOR_H

#define F_CPU 16000000

#include "bit_operations.h"
#include "TWI_Master.h"
#include "encoder.h"

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>


void motor_init(void);

void motor_calibrate(void);

void motor_set_range(void);

void motor_move(int16_t speed);

uint8_t motor_position(void);

#endif