
extern unsigned char* __uart_rcv_buf;
extern uint16_t __uart_rcv_buf_i;

void init_uart(uint16_t baud);

// Taken from atmega328p datasheet example
void __uart_transmit(unsigned char data);

// Taken from atmega328p datasheet example
unsigned char __uart_receive(void);

uint16_t uart_rcv_buf_size();

void uart_transmit_string(unsigned char* str, uint16_t len);

void uart_wait_for_reply();

void __uart_clear_rcv_buf();

uint16_t uart_copy_clear(unsigned char* dest);

