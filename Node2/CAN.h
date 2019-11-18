/** @file CAN.h
 *  @brief Header-file for the CAN driver. High level driver sending and receiving CAN messages.
 *  @author: Anastasia Lindbäck and Marie Skatvedt
 */

#ifndef CAN_H
#define CAN_H

#include <stdint.h>
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "MCP2515.h"
#include "SPI.h"

#include "bit_operations.h"

#define MCP_RX_BUFF_OP_MODE_BITS 0b01100000

/** Struct for message, defining id, length and data byte.
 */
typedef struct {
    uint8_t id;
    uint8_t length;
    uint8_t data[8]; 
} message;

extern message recent_msg;

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

/** Function for sending joystick position, buttons, slider positions and play-game flag via CAN to Node 2. 
 *  @param joystick position - Position of joystick, struct containing x and y-positions.
 *  @param Sliders slider_position - position of slider right and left.
 *  @param PLAY_GAME_FLAG - Flag set when play game is selected in the main menu.
 */
void CAN_transmit_game_info(uint8_t GAME_OVER_FLAG);


#endif