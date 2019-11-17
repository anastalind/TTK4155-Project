#ifndef MOTOR_H
#define MOTOR_H

#define F_CPU 16000000

#include "bit_operations.h"
#include "TWI_Master.h"
#include "encoder.h"

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>

typedef enum {LEFT, RIGHT} direction;


void motor_init(void);

void motor_calibrate(void);

void motor_set_range(void);

void motor_move(int16_t speed);

void motor_set_voltage(uint8_t voltage);

void motor_set_direction (direction dir);

uint8_t motor_position(void);

#endif