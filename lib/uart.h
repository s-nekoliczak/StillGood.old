
void init_uart(uint16_t baud);

// Taken from atmega328p datasheet example
void uart_transmit(char data);

// Taken from atmega328p datasheet example
unsigned char uart_receive(void);

void uart_transmit_string(char* str);

