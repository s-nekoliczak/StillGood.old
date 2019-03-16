
extern unsigned char __nfc_uid[4];

unsigned char __calc_dcs(unsigned char tfi, char* data, uint8_t tfi_data_len);

unsigned char __calc_lcs(unsigned char len);

void __build_cmd(unsigned char* cmd, unsigned char tfi, unsigned char* data, uint8_t tfi_data_len);

uint8_t __is_reply_successful(unsigned char success_code, uint8_t check_status);

uint8_t nfc_wakeup();

uint8_t nfc_inlistpsvtarget();

uint8_t nfc_authenticate();

uint8_t nfc_read_block(unsigned char* payload, unsigned char addr);

uint8_t nfc_write_block(unsigned char* payload, unsigned char addr);
