
#include <stdio.h>
#include <string.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/setbaud.h>

void init_uart(uint16_t baud) {
    UBRR0H = (baud>>8);
    UBRR0L = baud;

    UCSR0A = (0<<U2X0);         // Disable double speed

    sei();

    // Enable The receiver and transmitter
    UCSR0B =
            (1 << RXCIE0)       // enable receiver interrupt
        |   (1 << RXEN0)        // enable receiver
        |   (1 << TXEN0);       // enable transmitter

    UCSR0C =
            (0 << UMSEL01)      // asynchronous
        |   (0 << UMSEL00)      // asynchronous
        |   (0 << UPM01)        // no parity
        |   (0 << UPM00)        // no parity
        |   (0 << USBS0)        // 1 stop bit
        |   (1 << UCSZ01)       // 8-bit message size
        |   (1 << UCSZ00)       // 8-bit message size
        |   (0 << UCPOL0);      // Disable clock polarity for async mode

}

// Taken from atmega328p datasheet example
void uart_transmit(char data)
{
    while (!( UCSR0A & (1<<UDRE0)))
        ;
    UDR0 = data;
}

// Taken from atmega328p datasheet example
unsigned char uart_receive(void)
{
    while (!(UCSR0A & (1<<RXC0)))
        ;
    return UDR0;
}

void uart_transmit_string(char* str) {
    uint16_t len = strlen(str);

    for (uint16_t i = 0; i < len; ++i) {
        uart_transmit(str[i]);
    }
}

