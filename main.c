
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// in-house libraries
#include <eeprom.h>
#include <uart.h>
#include <nfc.h>
#include <nhd_lcd.h>
#include <i2c.h>

#include <util/delay.h>


//temp defines
#include <avr/interrupt.h>

#define RTC_ADDR        0x68


static void init_mcu(void) {
    // No clock divider.
    CLKPR =
            (1 << CLKPCE)
        |   (0 << CLKPS3)
        |   (0 << CLKPS2)
        |   (0 << CLKPS1)
        |   (0 << CLKPS0);

}


int main() {

    init_mcu();
    // 1/0x1 per the datasheet for 3.6864MHz/115200 baud
    //
    init_uart(0x1);
    // init_spi();
    // nhd_lcd_base_init();


    i2c_init();
    uint8_t st = 0;

    // Step 1: Write march/0x03 to addr 0x05 for month

    // Error codes: pg 273, table 26-3
    // 0x08/0x10
    st = i2c_start_trans();
    // 0x18/0x20
    st = i2c_send_addr(RTC_ADDR, 0);
    // 0x28/0x30
    st = i2c_send_dbyte(0x05);   // Set month addr
    st = i2c_send_dbyte(0x04);   // Set month data
    i2c_stop_send();



    // Step 2: Reset addr to 0x05 for reading in step 3

    // Error codes: pg 273, table 26-3
    // 0x08/0x10
    st = i2c_start_trans();
    // 0x18/0x20
    st = i2c_send_addr(RTC_ADDR, 0);
    // 0x28/0x30
    st = i2c_send_dbyte(0x05);   // Set month addr



    // Step 3: Read data at addr 0x05

    // Error codes: pg 277, table 26-4
    // 0x08/0x10
    st = i2c_start_trans();     // repeated start
    // 0x40/0x48
    st = i2c_send_addr(RTC_ADDR, 1);
    // 0x50/0x58
    st = i2c_rcv_dbyte();
    uint8_t r_data = 99;
    if (st == 0x50) {
        r_data = i2c_read_data();
    }
    i2c_stop_rcv();



    // Step 4: output findings

    char buf[10];
    uart_transmit_string("value: ", 7);
    snprintf(buf, 10, "%d", r_data);
    uart_transmit_string(buf, strlen(buf));
    uart_transmit_string("\r\n", 2);


    while(1) {
        ;
    }


}




    /*
    // Test eeprom
    eeprom_write_bytes(0x003C, "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz", 70);
    eeprom_read_bytes(0x003C, buf, 70);

    // Test NFC
    nfc_wakeup();
    nfc_inlistpsvtarget();
    nfc_authenticate();
    unsigned char data[16] = {0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB};
    nfc_write_block(data, 0x04);

    unsigned char payload[16];
    nfc_read_block(payload, 0x04);

    if (payload[0] == 0xAB) {
        PORTC |= (1<<PC5);
    }

    // Test NHD LCD
    nhd_lcd_init_screen();
    nhd_lcd_disp_on();
    nhd_lcd_wipe_screen();
    char test_str[16] = "new str testing";

    char header_str[23] = "";

    nhd_lcd_create_centered_str(test_str, 15, header_str);

    nhd_lcd_print_page_str(7, header_str, strlen(header_str), 0, 0);
    nhd_lcd_print_page_str(6, test_str, strlen(test_str), 1, 0);
    nhd_lcd_print_page_str(5, test_str, strlen(test_str), 1, 0);
    nhd_lcd_print_page_str(4, test_str, strlen(test_str), 1, 0);
    nhd_lcd_print_page_str(3, test_str, strlen(test_str), 1, 0);
    nhd_lcd_print_page_str(2, test_str, strlen(test_str), 1, 0);
    nhd_lcd_print_page_str(1, test_str, strlen(test_str), 1, 0);
    nhd_lcd_print_page_str(0, test_str, strlen(test_str), 1, 0);
    nhd_lcd_sel_page(4);
    */
