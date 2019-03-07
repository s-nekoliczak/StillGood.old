
#include <avr/io.h>
#include <stdlib.h>
#include <string.h>

#include <eeprom.h>
#include <uart.h>
#include <nfc.h>
#include <nhd_lcd.h>

#include <util/delay.h>

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
    nhd_lcd_base_init();

    /*
    // Test eeprom
    eeprom_write_bytes(0x003C, "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz", 70);
    eeprom_read_bytes(0x003C, buf, 70);
    */

    /*
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
    */

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

    while (1) {
        ;
    }

}












