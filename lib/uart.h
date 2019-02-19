
extern unsigned char* __g_rcv;
extern unsigned char __g_rcv_i;

void init_uart(uint16_t baud);

// Taken from atmega328p datasheet example
void __uart_transmit(unsigned char data);

// Taken from atmega328p datasheet example
unsigned char __uart_receive(void);

void uart_transmit_string(unsigned char* str, uint16_t len);

void uart_wait_for_reply();

void __clear_g_rcv();

uint16_t uart_copy_clear(unsigned char* dest);

