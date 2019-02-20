
#include <avr/io.h>
#include <stdlib.h>
#include <string.h>

#include <eeprom.h>
#include <uart.h>
#include <nfc.h>

static void init_mcu(void) {
    // No clock divider.
    CLKPR =
        (CLKPCE << 1)
        | (CLKPS3 << 0)
        | (CLKPS2 << 0)
        | (CLKPS1 << 0)
        | (CLKPS0 << 0);

}

int main() {

    // Light for testing receives
    DDRC = 0xFF;

    init_mcu();
    // 1/0x1 per the datasheet for 3.6864MHz/115200 baud
    //
    init_uart(0x1);

    init_spi();

    /*
    // Test eeprom
    eeprom_write_bytes(0x003C, "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz", 70);
    eeprom_read_bytes(0x003C, buf, 70);
    */

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

    while (1) {
        ;
    }

}












