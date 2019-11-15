/** @file CAN.h
 *  @brief Header-file for the CAN driver. High level driver sending and receiving CAN messages.
 *  @author: Anastasia Lindbäck and Marie Skatvedt
 */

#ifndef CAN_H
#define CAN_H

#include <stdint.h>
#include <stdio.h>

#include "MCP2515.h"
#include "SPI.h"

#include "bit_operations.h"

/** Struct for message, defining id, length and data byte.
 */
typedef struct {
    uint8_t id;
    uint8_t length;
    uint8_t data[8]; 
} message;


/** Function for initializing CAN.
 */
int CAN_init(void);

/** Function for sending a message with a given id and data using MCP2515 for CAN communication.
 *  @param message msg - message is struct including id, data and length of message
 */
void CAN_send_message(message msg);

/** Function for receiving a message with a given id and data using MCP2515 for CAN communication.
 *  @return uint8_t message- The message received
 */
message CAN_data_receive(void);

/** 
 */
void CAN_error(void);

/** 
 */
void CAN_transmit_complete(void);

/** 
 */
void CAN_int_vect(void);


#endif