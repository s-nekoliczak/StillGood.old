
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

    /*
    rtc_send_year(2019, 1);
    rtc_send_month(2, 1);
    rtc_send_date(29, 1);
    */
    // rtc_send_sec(5, 1);
    uint8_t data = rtc_rcv_sec(1);
    // rtc_clock_start(1);
    // rtc_clock_stop(1);


    char buf[10];
    for (uint8_t i = 0; i < 1; ++i) {
        uart_transmit_string("value: ", 7);
        snprintf(buf, 10, "%d", data);
        uart_transmit_string(buf, strlen(buf));
        uart_transmit_string("\r\n", 2);
    }

    while(1) {
        ;
    }

}


