
#include <avr/io.h>

#include <eeprom.h>
#include <uart.h>

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

    init_mcu();
    // 1/0x1 per the datasheet for 3.6864MHz/115200 baud
    //
    init_uart(0x1);

    init_spi();

    char buf[100] = "";

    eeprom_write_bytes(0x003C, "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz", 70);
    eeprom_read_bytes(0x003C, buf, 70);

    uart_transmit_string("Value read: ");
    uart_transmit_string(buf);
    uart_transmit_string("\r\n");

    while (1) {
        ;
    }

}
