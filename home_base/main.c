
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
#include <rtc.h>
#include <bluetooth.h>


#include <util/delay.h>


//temp defines
#include <avr/interrupt.h>

volatile uint8_t uart_replied;


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

    uart_replied = 0;

    init_mcu();
    // 1/0x1 per the datasheet for 3.6864MHz/115200 baud
    //
    init_uart(0x1, 10);
    // init_spi();
    // i2c_init();

/*
    _delay_ms(200);
    bt_cmd_init();
    _delay_ms(200);
    bt_cmd_set_mode(0);
    _delay_ms(200);
    bt_cmd_set_device_name("sg_remote");
    _delay_ms(200);
    bt_cmd_set_pin("9876");
    _delay_ms(200);
    bt_cmd_kill();
    _delay_ms(200);
    */

    while(1) {
        _delay_ms(10);
        if (uart_have_reply()) {
            uint16_t rep_len = uart_rcv_buf_size();
            unsigned char* rep = (unsigned char*)calloc(rep_len, sizeof(unsigned char));
            uart_copy_clear(rep);
            // uart_clear();
            // if (strcmp(rep, "abc") == 0) {
            if (rep[0] == 'a') {
                uart_transmit_string("got abc\n", 8);
            } else {
                uart_transmit_string("wrong\n", 6);
            }
            free(rep);
        }
    }

}


