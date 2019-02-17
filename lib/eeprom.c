
#include <stdio.h>
#include <string.h>

#include <avr/io.h>
#include <util/delay.h>

// Write in process bit
#define EEPROM_BIT_WIP              0b00000001

// Write enabled latch bit
#define EEPROM_BIT_WEL              0b00000010

#define EEPROM_CMD_READ             0b00000011
#define EEPROM_CMD_WRITE            0b00000010

// Reset write enable latch (disable write operations)
#define EEPROM_CMD_WRDI             0b00000100

// Enable write latch (enable write operations)
#define EEPROM_CMD_WREN             0b00000110

// Read status register
#define EEPROM_CMD_RDSR             0b00000101

// Write status register
#define EEPROM_CMD_WRSR             0b00000001

#define EEPROM_PAGE_SIZE            0x40
#define EEPROM_PAGE_SIZE_MASK       0x3F
#define EEPROM_FIRST_ADDR           0x0000
// Size of EEPROM in bytes
#define EEPROM_SIZE                 0x8000

#define EEPROM_PORT                 PORTB
#define EEPROM_DDR                  DDRB

#define EEPROM_SS                   PB2
#define EEPROM_MOSI                 PB3
#define EEPROM_MISO                 PB4
#define EEPROM_SCK                  PB5

#define EEPROM_SS_SELECT            EEPROM_PORT &= ~(1 << EEPROM_SS)
#define EEPROM_SS_DESELECT          EEPROM_PORT |= (1 << EEPROM_SS)

void init_spi() {

    EEPROM_DDR = (1 << EEPROM_SS) | (1 << EEPROM_MOSI) | (1 << EEPROM_SCK);

    // Pull SS high to avoid accidental communication with slave.
    EEPROM_PORT |= (1 << EEPROM_SS);

    SPCR =
            (1 << SPE)      // Enable SPI
        |   (1 << MSTR)     // Set to master
        |   (1 << SPR1)
        |   (1 << SPR0);
}

char spi_receive() {

    while (!(SPSR & (1<<SPIF)))
        ;

    return SPDR;
}

// Call spi_send(0) if waiting for a response
void spi_send(char byte) {

    SPDR = byte;

    while (!(SPSR & (1<<SPIF)))
        ;
}

void eeprom_read_bytes(uint16_t addr, char * str, uint16_t len) {

    EEPROM_SS_SELECT;

    memset(str, 0, strlen(str));

    spi_send(EEPROM_CMD_READ);
    spi_send(0xFF & (addr>>8));
    spi_send(0xFF & (addr));

    for (uint16_t i = 0; i < len; ++i) {
        spi_send(0);
        str[i] = spi_receive();
    }

    EEPROM_SS_DESELECT;
}

/*
Only writes to one page. This _WON'T_ start writing to a subsequent page if the
length is long enough. It will rather wrap around and write to the beginning
of the current page per the datasheet's notes. Call eeprom_write_bytes to avoid
that wrapping issue and to write bytes sequentially regardless of page breaks.
*/
void eeprom_write_page(uint16_t addr, char * str, uint16_t len) {

    _delay_ms(1);

    EEPROM_SS_SELECT;

    spi_send(EEPROM_CMD_WREN);

    EEPROM_SS_DESELECT;
    EEPROM_SS_SELECT;

    spi_send(EEPROM_CMD_WRITE);
    spi_send(0xFF & (addr>>8));
    spi_send(0xFF & (addr));

    for (uint16_t i = 0; i < len; ++i) {
        spi_send(str[i]);
    }

    EEPROM_SS_DESELECT;

    _delay_ms(1);
}

void eeprom_write_bytes(uint16_t addr, char * str, uint16_t len) {

    uint16_t pages = ((addr + len) / EEPROM_PAGE_SIZE) + 1
                        - (addr / EEPROM_PAGE_SIZE);

    uint16_t curr_addr = addr;
    uint16_t bytes_left = len;

    for (uint16_t i = 0; i < pages; ++i) {

        uint8_t write_len = EEPROM_PAGE_SIZE
                            - (EEPROM_PAGE_SIZE_MASK & curr_addr);

        if (bytes_left < write_len) {
            write_len = bytes_left;
        }

        // Go back to first addr if we hit the last address.
        if (curr_addr >= EEPROM_SIZE) {
            curr_addr = EEPROM_FIRST_ADDR;
        }

        eeprom_write_page(curr_addr, str+(len - bytes_left), write_len);

        curr_addr += write_len;
        bytes_left -= write_len;
    }
}

