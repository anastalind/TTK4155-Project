/** @file CAN.c
 *  @brief c-file for the CAN driver. High level driver sending and receiving CAN messages.
 *  @authors: Anastasia Lindbäck and Marie Skatvedt
 */

#include "CAN.h"
#include <util/delay.h>

//int CAN_INTERRUPT_FLAG = 0;


/** Function for initializing CAN
 */
int CAN_init(void){
    // Reset MCP2515 to configuration mode and test self
    MCP_init();

    MCP_bit_modify(MCP_CANINTE, 0b11, MCP_RX_INT); //Enable all receive interrupts
    // INT1 intflag is cleared by writing 1 to INTF1
    set_bit(GIFR, INTF1);
    // Enable interrupt on PD3
    set_bit(GICR, INT1);

    // Set normal mode
	MCP_bit_modify(MCP_CANCTRL, MODE_MASK, MODE_NORMAL);
    
    uint8_t value;    
    value = MCP_read(MCP_CANSTAT);

    printf("Value: %i\n\r", value);

    if ((value & MODE_MASK) != MODE_NORMAL) {
        printf("MCP2515 is not in NORMAL mode!\n\r");
    }

    else {
        printf("MCP2515 is in NORMAL mode!\n\r");
    }

    return 0;
}

/** Function for sending a message with a given id and data using MCP2515 for CAN communication.
 *  @param message msg - message is struct including id, data and length of message
 */
void CAN_send_message(message msg){

    // Write id for transmit buffers enabled to send to SIDH and SIDL registers
    MCP_write(MCP_TXB0SIDH, (msg.id >> 3));
    MCP_write(MCP_TXB0SIDL, (msg.id << 5));

    // Write data length to DLC transmit register
    MCP_write(MCP_TXB0DLC,msg.length);

    // 
    uint8_t i; 
    for (i = 0; i < msg.length; i++){
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
    for (uint8_t i = 0; i < msg.length; i++){
        msg.data[i] = MCP_read(MCP_RXB0D + i);
    }

    // Set interrupt flag to clear to send several times
    MCP_write(MCP_CANINTF, 0x00);

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


/** Function for testing transmit in loop-back mode.
 */
 void CAN_transmit_loopback_test(void){
    //sei();
    //CAN_init();
    message msg;
    msg.data[0] = 0xff;
    msg.id =1;
    msg.length =1;
    int stop = 1;
    while(stop<10) {
        CAN_send_message(msg);

        message received = CAN_data_receive();
        
        for (int i=0; i < received.length; i++){
            printf("%u",received.data[i]);
        }
        stop++;    
    }
}


/** Interrupt vector function for CAN.
 *  @param INT1_vect - interrupt vector for CAN. 
 */

ISR(INT1_vect){
    //CAN_INTERRUPT_FLAG = 1;
    //printf("In CAN INTERRUPT, FLAG = %i \n\r", CAN_INTERRUPT_FLAG);
}
