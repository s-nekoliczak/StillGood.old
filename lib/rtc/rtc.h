
uint8_t rtc_send_data(uint8_t addr, uint8_t* data, uint8_t data_len,
                                uint8_t is_stop);

uint8_t rtc_rcv_data(uint8_t addr, uint8_t* data, uint8_t data_len, uint8_t is_stop);

uint8_t rtc_set_year(uint16_t years);

uint16_t rtc_get_year();

