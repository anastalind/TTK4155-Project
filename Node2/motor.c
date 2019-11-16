/** @file motor.c
 *  @brief c-file for controlling the speed of the motor
 *  @authors: Anastasia Lindbäck and Marie Skatvedt
 */

#include "motor.h"

#define RESOLUTION 255

int LEFT_ENCODER_VALUE = -200;
int RIGHT_ENCODER_VALUE = 8337;

int current_encoder_value = 0;


/** Function for initializing motor by initializing TWI and enabling outputs and inputs from ATMega2560 (MJ1 and MJ2).
 */
void motor_initialize(void){

    // Initialize TWI/I2C-bus 
    TWI_Master_Initialise();

    // Enable motor
    set_bit(DDRH,PH4); // EN of MJ1
    set_bit(PORTH,PH4); // Set EN pin high to enable motor


    // Enable direction as output
    set_bit(DDRH,PH1);  // DIR of MJ1

    // Enable encoder as output
    set_bit(DDRH,PH5); // !OE of MJ1
    set_bit(DDRH,PH3); // SEL of MJ1
    set_bit(DDRH,PH6); // !RST of MJ1

    // Reset encoder
    reset_motor_encoder();

    // Enable the 8-bits from the ADC as inputs
    clear_bit(DDRK,0);
    clear_bit(DDRK,1);
    clear_bit(DDRK,2);
    clear_bit(DDRK,3);
    clear_bit(DDRK,4);
    clear_bit(DDRK,5);
    clear_bit(DDRK,6);
    clear_bit(DDRK,7);

    // Calibrate the motor to make sure we know the position and position-limits before starting.
    motor_calibrate();
}

/** Function for resetting the motor encoder by toggling RST from MJ1.
 */
void reset_motor_encoder(void){
    // !RST resets the counter.
    clear_bit(PORTH, PH6);
    _delay_us(200);
    set_bit(PORTH, PH6);
}


/** Function for reading the encoder counter.
 *  Reading motor encoder - Movement increases or decreases an internal 16 bits counter.
 *  @return (int16_t) ((high_byte << 8) | low_byte) - Motor encoder output.
 */
int16_t read_motor_encoder(void){

    // !OE pin of MJ1 driven low to allow the counter to appear on MJ2.
    clear_bit(PORTH,PH5);

    // SEL of MJ1 selects either high byte (0) or low byte (1) on the pins. Select low to get high (MSB)
    clear_bit(PORTH,PH3);

    // Wait in 20 micro seconds
    _delay_us(200);

    // Read MSB of ADC input
    uint8_t high_byte = PINK;

    // SEL of MJ1 selects either high byte (0) or low byte (1) on the pins. Select high to get low (LSB).
    set_bit(PORTH,PH3);

    // Wait in 20 micro seconds
    _delay_us(200);

    // Read LSB of ADC input
    uint8_t low_byte = PINK;

    // Reset encoder 
    reset_motor_encoder();

    // Set !OE high to disbale output of encoder
    set_bit(PORTH,PH5);

    return (int16_t) ((high_byte << 8) | low_byte);

}


/** Function for setting the speed of the motor by sending the desired voltage to the motor box via TWI.
 *  @param uint8_t DAC_voltage - The desired voltage for the motor (0-5V)
 */
void set_motor_speed(uint8_t DAC_voltage){
    
    uint8_t DAC_voltage_msg[3];

    // Address
    DAC_voltage_msg[0] = 0b01010000;
    // Command
    DAC_voltage_msg[1] = 0b00000000;
    // Data
    DAC_voltage_msg[2] = DAC_voltage; 

    TWI_Start_Transceiver_With_Data(DAC_voltage_msg, 3);
}


/** Function for setting the direction of the motor by setting or clearing the DIR pin in MJ1 on motor box.
 *  @param motor_direction direction - Enum value that is either LEFT, RIGHT or NEUTRAL.
 */
void set_motor_direction(motor_direction direction){
    switch(direction) {
        case LEFT:
            clear_bit(PORTH, PH1);
            break;
        case RIGHT:
            set_bit(PORTH, PH1);
            break;
        case NEUTRAL:
            break;
    }
}


/** Function for controlling the motor speed by passing in desired voltage value (negative values sets direction to left, positive to right)
 *  @param int16_t speed - desired speed.
 */
void motor_speed_controller(int16_t speed) {
    //printf("Initialized DAC voltage: %u \n\r", DAC_voltage);
    uint8_t DAC_voltage;

    if (speed < 0) {
        clear_bit(PORTH, PH1);
        DAC_voltage = (-1) * speed;
    }

    else if (speed >= 0) {
        set_bit(PORTH, PH1);
        DAC_voltage = speed; 
    }

    set_motor_speed(DAC_voltage);
}


/** Function for calibrating motor and reading min and max encoder values
 */ 
void motor_calibrate(void) {
	motor_speed_controller(-100);
    _delay_ms(10000);

	int16_t cur_rot = read_motor_encoder();
	int16_t prev_rot = cur_rot + 200;

    // Not quite sure about this
	while (prev_rot != cur_rot) {
		prev_rot = cur_rot;
		_delay_ms(40);
		cur_rot = read_motor_encoder();
	}
	reset_motor_encoder();
	motor_speed_controller(0);

    LEFT_ENCODER_VALUE = cur_rot;
    //printf("SET ENCODER VALUE %u \n\n\r", current_encoder_value);
}

/** Function for reading the position-limits of the board and returning the current position of the motor.
 *  @return current_position - a value between (0, 255) representing the motors position.
 */ 
uint8_t get_motor_position(void){

    int16_t read_encoder_value = (-1) * read_motor_encoder();
    printf("READ ENCODER VALUE %u \n\n\r", read_encoder_value);
    
    if (read_encoder_value > RIGHT_ENCODER_VALUE) {
        read_encoder_value = current_encoder_value;
    }

    else if (read_encoder_value < LEFT_ENCODER_VALUE) {
        read_encoder_value = current_encoder_value;
    }

    current_encoder_value = read_encoder_value;
    //printf("SET ENCODER VALUE %u \n\n\r", current_encoder_value);
    

    uint8_t current_position = (uint8_t)(((read_encoder_value - LEFT_ENCODER_VALUE)/RIGHT_ENCODER_VALUE)*RESOLUTION);
    //printf("PROCESS VALUE %u \n\n\r", current_position);

    return current_position;
}

/** Function for testing the slider-control and the motor. 
 *  @param message msg - position message.
 */
void slider_controller_test(message msg) {

    uint8_t ref_pos = msg.data[3];
    //printf("Received slider data %u\n\n\r", ref_pos);

    uint8_t curr_pos = get_motor_position();
    //printf("Current position %u\n\n\r", curr_pos);   

    int8_t diff = (int8_t)(ref_pos - curr_pos);


    //printf("Difference between ref pos and curr pos %i\n\n\r", diff);   

    if (diff > 0) {
        set_motor_direction(LEFT);
        set_motor_speed(100);
        //printf("Motor direction: left\n\r");
    }

    else if (diff < 0) {
        set_motor_direction(RIGHT);
        set_motor_speed(100);
        //printf("Motor direction: right\n\r");   
    }

    else {
        set_motor_direction(NEUTRAL);
        set_motor_speed(0);
        //printf("Motor direction: neutral\n\r");
    }
}