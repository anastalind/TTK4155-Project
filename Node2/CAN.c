/** @file CAN.c
 *  @brief c-file for the CAN driver. High level driver sending and receiving CAN messages.
 *  @authors: Anastasia Lindbäck and Marie Skatvedt
 */

#include "CAN.h"

message recent_msg; 

/** Function for initializing CAN communication.
 */
int CAN_init(void){
    /*
    // Enable interrupt for CAN on node 2
    // Falling edge
    clear_bit(EICRA, ISC20);
    set_bit(EICRA, ISC21);

    // Enable interrupt on PD2 (19 on Arduino shield)
    set_bit(EIMSK, INT2);

    // Clear interrupt flag on PD2
    set_bit(EIFR, INTF2);
    */
    
    // Reset MCP2515 to configuration mode and test self
    MCP_init();

    MCP_bit_modify(MCP_RXB0CTRL, MCP_RX_BUFF_OP_MODE_BITS, 0xFF);

    // Set MCP to normal mode
    MCP_bit_modify(MCP_CANCTRL, MODE_MASK, MODE_NORMAL);

    // Enable receive interrupts
    MCP_bit_modify(MCP_CANINTE, MCP_INT_MASK, MCP_RX_INT);

    // Clear interrupt flag
    MCP_bit_modify(MCP_CANINTF, MCP_INT_MASK, 0);

    uint8_t value;    
    value = MCP_read(MCP_CANSTAT);

    if ((value & MODE_MASK) != MODE_NORMAL) {
        printf("MCP2515 is not in NORMAL mode!\n\r");
    }

    else {
        printf("MCP2515 is in NORMAL mode!\n\r");
    }

    return 0;
}

/** Function for sending a message with a given id and data using MCP2515 for CAN communication.
 *  @param message msg - Struct including id, data and length of message
 */
void CAN_send_message(message msg){

    // Write id for transmit buffers enabled to send to SIDH and SIDL registers
    MCP_write(MCP_TXB0SIDH, (msg.id >> 3));
    MCP_write(MCP_TXB0SIDL, (msg.id << 5));

    // Write data length to DLC transmit register
    MCP_write(MCP_TXB0DLC, msg.length);

    for (uint8_t i = 0; i < msg.length; i++){
        MCP_write((MCP_TXB0D + i), msg.data[i]);
    }

    MCP_request_to_send(0);
}


/** Function for receiving a message with a given id and data using MCP2515 for CAN communication.
 *  @return message message - The message received.
 */
message CAN_data_receive(void){

    message msg;

    // Read message id
    msg.id = (MCP_read(MCP_RXB0SIDH) << 3) | (MCP_read(MCP_RXB0SIDL) >> 5);

    // Read message length
    msg.length = MCP_read(MCP_RXB0DLC);// & 0b00001111;

    // Read each bit of data 
    for (uint8_t i = 0; i < msg.length; i++){
        msg.data[i] = MCP_read(MCP_RXB0D + i);   
    }
    // Set interrupt flag to clear to send several times
    MCP_write(MCP_CANINTF, 0x00);

    return msg;
}


/** Function for testing transmit in loop-back mode.
 */
 void CAN_transmit_loopback_test(void){
    CAN_init();
    message msg;

    msg.id =1;
    msg.length = sizeof(msg.data);
    int stop = 1;
    for(int j = 0; j < 8; j++){
        msg.data[j] = j*2;
    }
    while(stop<10) {
        CAN_send_message(msg);

        message received = CAN_data_receive();
        printf("ID: %d\n\r",received.id);
        printf("Length : %d\n\r", received.length);
        for (int i = 0; i < received.length; i++){
            printf("%d ",received.data[i]);
        }
        stop++;    
    }
}

/** Function for sending joystick position, buttons, slider positions and play-game flag via CAN to Node 2. 
 *  @param joystick position - Position of joystick, struct containing x and y-positions.
 *  @param Sliders slider_position - position of slider right and left.
 *  @param PLAY_GAME_FLAG - Flag set when play game is selected in the main menu.
 */
void CAN_transmit_game_info(uint8_t GAME_OVER_FLAG) {
    message msg;
    msg.length = 2;
    msg.id = 1;

    //msg.data[0] = score;
    msg.data[1] = GAME_OVER_FLAG;

    CAN_send_message(msg);  
}



/** Interrupt vector function for CAN.
 *  @param INT2_vect - interrupt vector for CAN. 
 */
ISR(INT2_vect){
    //printf("CAN INTERRUPT \n\r");
    //recent_msg = CAN_data_receive();
}
