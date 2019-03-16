
void i2c_init();

void i2c_wait_for_hdwr_rspn();

uint8_t i2c_status();

// Write is 0, read is 1.
void i2c_set_addr(uint8_t addr, uint8_t w_r);

void i2c_set_dbyte(uint8_t data);

uint8_t i2c_read_data();

uint8_t i2c_start_trans();

// Write is 0, read is 1.
uint8_t i2c_send_addr(uint8_t addr, uint8_t w_r);

uint8_t i2c_send_dbyte(uint8_t byte);

uint8_t i2c_rcv_dbyte();

uint8_t i2c_stop_send();

uint8_t i2c_stop_rcv();


