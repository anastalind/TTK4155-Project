/** @package motor.c
 *  c-file for controlling the speed of the motor
 *  @authors: Anastasia Lindbäck and Marie Skatvedt
 */


/** Initializing motor by initializing TWI and enabling outputs and inputs from ATMega2560 (MJ1 and MJ2).
 */
void motor_initialize(void){

    // Initialize TWI/I2C-bus 
    TWI_Master_Initialise();

    // Enable motor
    set_bit(DDRH,PH4); // EN of MJ1
    set_bit(PORTH,PH4); // Set EN pin high to enable motor


    // Enable direction as output
    set_bit(DDRH,PH1);  // DIR of MJ1
    // provide an analog voltage 0-5v on DA1 of MJEX to control the output voltage to the motor

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

}

/** Resetting the motor encoder by toggling RST from MJ1.
 */
void reset_motor_encoder(void){
    // !RST resets the counter.
    toggle_bit(PORTH,PH6);
}

/** Function for reading the encoder counter.
 *  Reading motor encoder - Movement increases or decreases an internal 16 bits counter.
 */
void read_motor_eancoder(void){

    // !OE pin of MJ1 driven low to allow the counter to appear on MJ2.
    clear_bit(PORTH,PH5);

    // SEL of MJ1 selects either high byte (0) or low byte (1) on the pins. Select low to get high (MSB)
    clear_bit(PORTH,PH3);

    // Wait in 20 micro seconds
    _delay_ms(0.02);

    // Read MSB of ADC input
    uint8_t high_byte = PINK;

    // SEL of MJ1 selects either high byte (0) or low byte (1) on the pins. Select high to get low (LSB).
    set_bit(PORTH,PH3);

    // Wait in 20 micro seconds
    _delay_ms(0.02);

    // Read LSB of ADC input
    uint8_t low_byte = PINK;

    // Reset encoder
    reset_motor_encoder();

    // Set !OE high to disbale output of encoder
    set_bit(PORTH,PH5);
}


// Motor speed to be controlled by joysticks position
void set_motor_speed(void){
    // Setting motor speed by adjusting DAC voltage

}

void set_motor_direction(void){
    // Select direction with DIR pin
}


    