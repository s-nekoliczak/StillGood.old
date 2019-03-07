#include <nhd_lcd_macros.h>

void nhd_lcd_light_on();

void nhd_lcd_light_off();

void nhd_lcd_base_init();

void nhd_lcd_init_screen();

void nhd_lcd_disp_on();

void nhd_lcd_disp_off();

void nhd_lcd_reset();

char col_addr_upper_cmd(uint8_t col_num);

char col_addr_lower_cmd(uint8_t col_num);

char line_addr_cmd(uint8_t line_num);

char page_addr_cmd(uint8_t page_num);

char page_addr_cmd(uint8_t page_num);

void nhd_lcd_wipe_screen();

void nhd_lcd_sleep();

void nhd_lcd_wakeup();

void char_to_colarr(char c, char* colarr);

void create_page_str(char* in_str, uint8_t str_len, char* ret_str);

void nhd_lcd_print_page_str(uint8_t page, char* str, uint8_t str_len, uint8_t is_selectable, uint8_t is_selected);

void nhd_lcd_sel_page(uint8_t page);

void nhd_lcd_create_centered_str(char* in_str, uint8_t in_str_len, char* out_str);

