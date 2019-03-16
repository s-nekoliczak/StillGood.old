
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
    i2c_init();

    rtc_set_year(2019);
    uint16_t year = rtc_get_year();

    char buf[10];
    for (uint8_t i = 0; i < 1; ++i) {
        uart_transmit_string("value: ", 7);
        snprintf(buf, 10, "%d", year);
        uart_transmit_string(buf, strlen(buf));
        uart_transmit_string("\r\n", 2);
    }

    while(1) {
        ;
    }

}


