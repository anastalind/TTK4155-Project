#ifndef ADDRESSES_H
#define ADDRESSES_H
// ADC
#define adc_addr ((volatile char*) 0x1400)


//OLED 
#define cmnd_oled_addr ((volatile char*) 0x1000)
#define data_oled_addr ((volatile char*) 0x1200)

    // OLED command addresses
    #define oled_lower_col_addr 0x00
    #define oled_higher_col_addr 0x10
    #define oled_page_start_addr 0xb0


// SRAM
#define sram_addr ((volatile char*) 0x1800)

#endif