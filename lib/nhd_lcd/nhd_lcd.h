#include <nhd_lcd_macros.h>

void nhd_lcd_light_on();

void nhd_lcd_light_off();

void nhd_lcd_init();

void nhd_lcd_disp_on();

void nhd_lcd_disp_off();

void nhd_lcd_reset();

char __nhd_lcd_col_addr_upper_cmd(uint8_t col_num);

char __nhd_lcd_col_addr_lower_cmd(uint8_t col_num);

char __nhd_lcd_line_addr_cmd(uint8_t line_num);

char __nhd_lcd_row_addr_cmd(uint8_t row_num);

void nhd_lcd_wipe_screen();

void nhd_lcd_sleep();

void nhd_lcd_wakeup();

void __nhd_lcd_char_to_colarr(char c, char* colarr);

void __nhd_lcd_create_row_str(char* in_str, uint8_t str_len, char* ret_str);

void nhd_lcd_print_row_str(uint8_t row, char* str, uint8_t str_len, uint8_t is_selectable, uint8_t is_selected);

void nhd_lcd_sel_row(uint8_t row, uint8_t set_sel);

void nhd_lcd_create_centered_str(char* in_str, uint8_t in_str_len, char* out_str);

