
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


/*
74HC4052E mux notes
Connect S1 pin to GND

A Bank is for MCU TXD / MUX RXD
B Bank is for MCU RXD / MUX TXD

0 is for NFC
1 is for BLUETOOTH

A0 - NFC RXD
B0 - NFC TXD

A1 - BLUETOOTH RXD
B1 - BLUETOOTH TXD
*/

#define USEL_PORT               PORTD
#define USEL_DDR                DDRD
#define USEL_SWITCH             PD2
#define USEL_SEL                PD3

#define USEL_SWITCH_ON          USEL_PORT &= ~(1 << USEL_SWITCH)
#define USEL_SWITCH_OFF         USEL_PORT |= (1 << USEL_SWITCH)

#define USEL_SEL_AB_0           USEL_PORT &= ~(1 << USEL_SEL)
#define USEL_SEL_AB_1           USEL_PORT |= (1 << USEL_SEL)

void usel_uart_on() {
    USEL_SWITCH_ON;
};

void usel_uart_off() {
    USEL_SWITCH_OFF;
};

void usel_nfc() {
    USEL_SEL_AB_0;
};

void usel_bt() {
    USEL_SEL_AB_1;
};

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
    // i2c_init();

    DDRD = 0xFF;

    usel_uart_on();
    usel_nfc();

    USEL_DDR = (1 << PD2) | (1 << PD3);

    PORTC |= (1<<PC4);


    uint8_t rep_good;
    rep_good = nfc_wakeup();
    rep_good = nfc_inlistpsvtarget();
    rep_good = nfc_authenticate();

    unsigned char data[16] = {0xEF, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB};
    rep_good = nfc_write_block(data, 0x04);

    unsigned char payload[16];
    rep_good = nfc_read_block(payload, 0x04);


    if (payload[0] == 0xEF) {
        PORTC |= (1<<PC5);
    }

    while(1) {
        ;
    }

}


