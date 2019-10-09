/** @package CAN.c
 *  c-file for the CAN driver. High level driver sending and receiving CAN messages.
 *  @authors: Anastasia Lindbäck and Marie Skatvedt
 */

#include "CAN.h"


/** Function for initializing CAN
 */
int CAN_init(void){
    // Reset MCP2515 to configuration mode and test self
    MCP_init();

    // Set loopback mode
    MCP_bit_modify(MCP_CANCTRL, MODE_MASK, MODE_LOOPBACK);

    uint8_t value;    
    value = MCP_read(MCP_CANSTAT);

    if ((value & MODE_MASK) != MODE_LOOPBACK) {
        printf("MCP2515 is not in loop back mode!\n\r");
    }

    else {
        printf("MCP2515 is in loop back mode!\n\r");
    }
    return 0;
    // Initialize interrupt flags?
}

/** Function for sending a message with a given id and data using MCP2515 for CAN communication.
 *  @param message msg - message is struct including id, data and length of message
 */
void CAN_send_message(message msg){

    // Write id for transmit buffers enabled to send to SIDH and SIDL registers
    MCP_write(MCP_TXB0SIDH, (msg.id >> 3));
    MCP_write(MCP_TXB0SIDL, (msg.id << 5));

    // Write data length to DLC transmit register
    MCP_write(msg.length,MCP_TXB0DLC);

    // 
    uint8_t i; 
    for (i=0; i < msg.length; i++){
        MCP_write((MCP_TXB0D + i), msg.data[i]);
    }
    MCP_request_to_send(0);
}


/** Function for receiving a message with a given id and data using MCP2515 for CAN communication.
 *  @return uint8_t message- The message received
 */
message CAN_data_receive(void){
    message msg;

    //Read message id
    msg.id = (MCP_read(MCP_RXB0SIDH) << 3)+ (MCP_read(MCP_RXB0SIDL) >> 5);
    // Read message length
    msg.length = MCP_read(MCP_RXB0DLC);
    
    // Read each bit of data 
    uint8_t i; 
    for (i=0; i < msg.length; i++){
        msg.data[i] = MCP_read(MCP_RXB0D+i);
    }
    return msg;
}

/** 
 */
void CAN_error(void){

}

/** 
 */
void CAN_transmit_complete(void){

}

/** 
 */
void CAN_int_vect(void){
    // si fra om klar til å sende eller motta 
}

