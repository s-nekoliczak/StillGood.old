
#include <stdio.h>
#include <string.h>

#include <avr/io.h>
#include <util/delay.h>

#include <spi.h>
#include <spi_macros.h>
#include <eeprom.h>
#include <nhd_lcd_macros.h>
#include <nhd_lcd_letters.c>


const char __ltr_a[NHD_LCD_CHAR_WIDTH] =    {0x3F, 0x50, 0x50, 0x50, 0x3F, 0x00};
const char __ltr_b[NHD_LCD_CHAR_WIDTH] =    {0x7F, 0x49, 0x49, 0x39, 0x0F, 0x00};
const char __ltr_c[NHD_LCD_CHAR_WIDTH] =    {0x7F, 0x41, 0x41, 0x41, 0x41, 0x00};
const char __ltr_d[NHD_LCD_CHAR_WIDTH] =    {0x7F, 0x41, 0x41, 0x41, 0x3E, 0x00};
const char __ltr_e[NHD_LCD_CHAR_WIDTH] =    {0x7F, 0x49, 0x49, 0x49, 0x41, 0x00};
const char __ltr_f[NHD_LCD_CHAR_WIDTH] =    {0x7F, 0x48, 0x48, 0x48, 0x40, 0x00};
const char __ltr_g[NHD_LCD_CHAR_WIDTH] =    {0x7F, 0x41, 0x41, 0x49, 0x4F, 0x00};
const char __ltr_h[NHD_LCD_CHAR_WIDTH] =    {0x7F, 0x08, 0x08, 0x08, 0x7F, 0x00};
const char __ltr_i[NHD_LCD_CHAR_WIDTH] =    {0x41, 0x41, 0x7F, 0x41, 0x41, 0x00};
const char __ltr_j[NHD_LCD_CHAR_WIDTH] =    {0x47, 0x41, 0x7F, 0x40, 0x40, 0x00};
const char __ltr_k[NHD_LCD_CHAR_WIDTH] =    {0x7F, 0x08, 0x14, 0x22, 0x41, 0x00};
const char __ltr_l[NHD_LCD_CHAR_WIDTH] =    {0x7F, 0x01, 0x01, 0x01, 0x01, 0x00};
const char __ltr_m[NHD_LCD_CHAR_WIDTH] =    {0x7F, 0x20, 0x18, 0x20, 0x7F, 0x00};
const char __ltr_n[NHD_LCD_CHAR_WIDTH] =    {0x7F, 0x20, 0x1C, 0x02, 0x7F, 0x00};
const char __ltr_o[NHD_LCD_CHAR_WIDTH] =    {0x7F, 0x41, 0x41, 0x41, 0x7F, 0x00};
const char __ltr_p[NHD_LCD_CHAR_WIDTH] =    {0x7F, 0x48, 0x48, 0x48, 0x78, 0x00};
const char __ltr_q[NHD_LCD_CHAR_WIDTH] =    {0x7E, 0x42, 0x46, 0x7F, 0x01, 0x00};
const char __ltr_r[NHD_LCD_CHAR_WIDTH] =    {0x7F, 0x48, 0x4C, 0x7A, 0x01, 0x00};
const char __ltr_s[NHD_LCD_CHAR_WIDTH] =    {0x79, 0x49, 0x49, 0x49, 0x4F, 0x00};
const char __ltr_t[NHD_LCD_CHAR_WIDTH] =    {0x40, 0x40, 0x7F, 0x40, 0x40, 0x00};
const char __ltr_u[NHD_LCD_CHAR_WIDTH] =    {0x7F, 0x01, 0x01, 0x01, 0x7F, 0x00};
const char __ltr_v[NHD_LCD_CHAR_WIDTH] =    {0x7C, 0x02, 0x01, 0x02, 0x7C, 0x00};
const char __ltr_w[NHD_LCD_CHAR_WIDTH] =    {0x7E, 0x01, 0x0E, 0x01, 0x7E, 0x00};
const char __ltr_x[NHD_LCD_CHAR_WIDTH] =    {0x63, 0x14, 0x08, 0x14, 0x63, 0x00};
const char __ltr_y[NHD_LCD_CHAR_WIDTH] =    {0x60, 0x10, 0x0F, 0x10, 0x60, 0x00};
const char __ltr_z[NHD_LCD_CHAR_WIDTH] =    {0x43, 0x45, 0x49, 0x51, 0x61, 0x00};
const char __ltr_spc[NHD_LCD_CHAR_WIDTH] =  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
const char __ltr_arw[NHD_LCD_CHAR_WIDTH] =  {0x7F, 0x3E, 0x1C, 0x08, 0x00, 0x00};
const char __ltr_col[NHD_LCD_CHAR_WIDTH] =  {0x00, 0x36, 0x36, 0x00, 0x00, 0x00};

uint8_t has_header;


void nhd_lcd_light_on() {
    NHD_LCD_BL_ON;
}

void nhd_lcd_light_off() {
    NHD_LCD_BL_OFF;
}



void nhd_lcd_base_init() {
    NHD_LCD_DDR |=
            (1<<NHD_LCD_RESET)
        |   (1<<NHD_LCD_REG_SEL);
    NHD_LCD_LIGHT_DDR |=
            (1<<NHD_LCD_BL)
        |   (1<<NHD_LCD_RED)
        |   (1<<NHD_LCD_GREEN)
        |   (1<<NHD_LCD_BLUE);


    NHD_LCD_RESET_HIGH;
    SPI_SS_DESELECT;
    nhd_lcd_light_on();

    has_header = 0;
}

void nhd_lcd_init_screen() {
    SPI_SS_SELECT;
    NHD_LCD_REG_SEL_LOW;

    spi_send(NHD_LCD_ADC_NORM);
    spi_send(NHD_LCD_CMD_DISP_OFF);
    spi_send(NHD_LCD_OUTPUT_MODE_REV);
    spi_send(NHD_LCD_BIAS_1_9);
    spi_send(NHD_LCD_PWR_CTRL_SET_DEFAULT);
    spi_send(NHD_LCD_RESIST_RATIO_DEFAULT);
    spi_send(NHD_LCD_ELEC_VOL_DEFAULT);
    // Set col to 0.
    spi_send(0x10);
    spi_send(NHD_LCD_CMD_DISP_ON);

    SPI_SS_DESELECT;
}


void nhd_lcd_disp_on() {
    SPI_SS_SELECT;
    NHD_LCD_REG_SEL_LOW;
    spi_send(NHD_LCD_CMD_DISP_ON);
    SPI_SS_DESELECT;
}

void nhd_lcd_disp_off() {
    SPI_SS_SELECT;
    NHD_LCD_REG_SEL_LOW;
    spi_send(NHD_LCD_CMD_DISP_OFF);
    SPI_SS_DESELECT;

}

void nhd_lcd_reset() {
    SPI_SS_SELECT;
    spi_send(NHD_LCD_CMD_RESET);
    SPI_SS_DESELECT;

}

char col_addr_upper_cmd(uint8_t col_num) {
    return (0x1 << (NHD_LCD_BYTE_SIZE >> 1)) | (0xF & col_num);
}

char col_addr_lower_cmd(uint8_t col_num) {
    return (0xF & col_num);
}

char line_addr_cmd(uint8_t line_num) {
    return (0x4 << (NHD_LCD_BYTE_SIZE >> 1)) | (0x3F & line_num);
}

char page_addr_cmd(uint8_t page_num) {
    return (0xB << (NHD_LCD_BYTE_SIZE >> 1)) | (0xF & page_num);
}

void nhd_lcd_wipe_screen() {
    SPI_SS_SELECT;
    NHD_LCD_REG_SEL_LOW;

    uint8_t i = 0;
    for (i = 0; i < NHD_LCD_NUM_PAGES; ++i) {
        NHD_LCD_REG_SEL_LOW;
        SPI_SS_SELECT;
        spi_send(line_addr_cmd(0));
        spi_send(page_addr_cmd(i));
        spi_send(col_addr_upper_cmd(0));
        spi_send(col_addr_lower_cmd(0));

        for (uint8_t j = 0; j < NHD_LCD_PAGE_COLS_SIZE; ++j) {
            NHD_LCD_REG_SEL_HIGH;
            spi_send(0x00);
        }
        SPI_SS_DESELECT;
    }

    NHD_LCD_REG_SEL_LOW;
    SPI_SS_DESELECT;

}

/*
TODO sleep works but wakeup doesn't
*/
void nhd_lcd_sleep() {
    SPI_SS_SELECT;
    NHD_LCD_REG_SEL_LOW;

    // spi_send(NHD_LCD_STATIC_IND_OFF);
    spi_send(NHD_LCD_STATIC_IND_ON);
    spi_send(0x00);
    nhd_lcd_disp_off();
    spi_send(NHD_LCD_ALL_POINTS_ON);

    SPI_SS_DESELECT;
}

void nhd_lcd_wakeup() {
    SPI_SS_SELECT;
    NHD_LCD_REG_SEL_LOW;

    spi_send(NHD_LCD_STATIC_IND_ON);
    spi_send(0xFF);
    spi_send(NHD_LCD_ALL_POINTS_NORMAL);

    SPI_SS_DESELECT;
}

void char_to_colarr(char c, char colarr[NHD_LCD_CHAR_WIDTH]) {

    char fill[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00};

    switch (c) {
        case 'a':
            memcpy(colarr, __ltr_a, NHD_LCD_CHAR_WIDTH);
            return;
        case 'b':
            memcpy(colarr, __ltr_b, NHD_LCD_CHAR_WIDTH);
            return;
        case 'c':
            memcpy(colarr, __ltr_c, NHD_LCD_CHAR_WIDTH);
            return;
        case 'd':
            memcpy(colarr, __ltr_d, NHD_LCD_CHAR_WIDTH);
            return;
        case 'e':
            memcpy(colarr, __ltr_e, NHD_LCD_CHAR_WIDTH);
            return;
        case 'f':
            memcpy(colarr, __ltr_f, NHD_LCD_CHAR_WIDTH);
            return;
        case 'g':
            memcpy(colarr, __ltr_g, NHD_LCD_CHAR_WIDTH);
            return;
        case 'h':
            memcpy(colarr, __ltr_h, NHD_LCD_CHAR_WIDTH);
            return;
        case 'i':
            memcpy(colarr, __ltr_i, NHD_LCD_CHAR_WIDTH);
            return;
        case 'j':
            memcpy(colarr, __ltr_j, NHD_LCD_CHAR_WIDTH);
            return;
        case 'k':
            memcpy(colarr, __ltr_k, NHD_LCD_CHAR_WIDTH);
            return;
        case 'l':
            memcpy(colarr, __ltr_l, NHD_LCD_CHAR_WIDTH);
            return;
        case 'm':
            memcpy(colarr, __ltr_m, NHD_LCD_CHAR_WIDTH);
            return;
        case 'n':
            memcpy(colarr, __ltr_n, NHD_LCD_CHAR_WIDTH);
            return;
        case 'o':
            memcpy(colarr, __ltr_o, NHD_LCD_CHAR_WIDTH);
            return;
        case 'p':
            memcpy(colarr, __ltr_p, NHD_LCD_CHAR_WIDTH);
            return;
        case 'q':
            memcpy(colarr, __ltr_q, NHD_LCD_CHAR_WIDTH);
            return;
        case 'r':
            memcpy(colarr, __ltr_r, NHD_LCD_CHAR_WIDTH);
            return;
        case 's':
            memcpy(colarr, __ltr_s, NHD_LCD_CHAR_WIDTH);
            return;
        case 't':
            memcpy(colarr, __ltr_t, NHD_LCD_CHAR_WIDTH);
            return;
        case 'u':
            memcpy(colarr, __ltr_u, NHD_LCD_CHAR_WIDTH);
            return;
        case 'v':
            memcpy(colarr, __ltr_v, NHD_LCD_CHAR_WIDTH);
            return;
        case 'w':
            memcpy(colarr, __ltr_w, NHD_LCD_CHAR_WIDTH);
            return;
        case 'x':
            memcpy(colarr, __ltr_x, NHD_LCD_CHAR_WIDTH);
            return;
        case 'y':
            memcpy(colarr, __ltr_y, NHD_LCD_CHAR_WIDTH);
            return;
        case 'z':
            memcpy(colarr, __ltr_z, NHD_LCD_CHAR_WIDTH);
            return;
        case ' ':
            memcpy(colarr, __ltr_spc, NHD_LCD_CHAR_WIDTH);
            return;
        case '>':
            memcpy(colarr, __ltr_arw, NHD_LCD_CHAR_WIDTH);
            return;
        case ':':
            memcpy(colarr, __ltr_col, NHD_LCD_CHAR_WIDTH);
            return;
        default:
            memcpy(colarr, fill, NHD_LCD_CHAR_WIDTH);
            return;
    }
    
}

void create_page_str(char* in_str, uint8_t str_len, char* ret_str) {

    for (uint8_t i = 0; i < str_len; ++i) {
        char colarr[NHD_LCD_CHAR_WIDTH];
        char_to_colarr(in_str[i], colarr);
        for (uint8_t j = 0; j < NHD_LCD_CHAR_WIDTH; ++j) {
            ret_str[(i*NHD_LCD_CHAR_WIDTH)+j] = colarr[j];
        }
    }

    for (uint8_t i = str_len; i < NHD_LCD_NUM_CHARS_PER_LINE; ++i) {
        for (uint8_t j = 0; j < NHD_LCD_CHAR_WIDTH; ++j) {
            ret_str[(i*NHD_LCD_CHAR_WIDTH)+j] = 0x00;
        }
    }
}

void nhd_lcd_print_page_str(uint8_t page, char* str, uint8_t str_len, uint8_t is_selectable, uint8_t is_selected) {
    SPI_SS_SELECT;
    NHD_LCD_REG_SEL_LOW;

    uint8_t cols = NHD_LCD_PAGE_COLS_SIZE;

    char page_str[cols];
    create_page_str(str, str_len, page_str);

    NHD_LCD_REG_SEL_LOW;
    SPI_SS_SELECT;
    spi_send(line_addr_cmd(0));
    spi_send(page_addr_cmd(page));
    spi_send(col_addr_upper_cmd(0));
    spi_send(col_addr_lower_cmd(0));

    NHD_LCD_REG_SEL_HIGH;
    if (is_selectable) {
        cols -= NHD_LCD_CHAR_WIDTH;
        if (is_selected) {
            for (uint8_t i = 0; i < NHD_LCD_CHAR_WIDTH; ++i) {
                spi_send(__ltr_arw[i]);
            }
        } else {
            for (uint8_t i = 0; i < NHD_LCD_CHAR_WIDTH; ++i) {
                spi_send(0x00);
            }
        }
    }
    for (uint8_t i = 0; i < cols; ++i) {
        spi_send(page_str[i]);
    }

    NHD_LCD_REG_SEL_LOW;
    SPI_SS_DESELECT;
}

void nhd_lcd_sel_page(uint8_t page) {
    SPI_SS_SELECT;
    NHD_LCD_REG_SEL_LOW;

    char page_str[NHD_LCD_PAGE_COLS_SIZE];
    create_page_str(">", 1, page_str);

    NHD_LCD_REG_SEL_LOW;
    SPI_SS_SELECT;
    spi_send(line_addr_cmd(0));
    spi_send(page_addr_cmd(page));
    spi_send(col_addr_upper_cmd(0));
    spi_send(col_addr_lower_cmd(0));

    NHD_LCD_REG_SEL_HIGH;
    for (uint8_t i = 0; i < NHD_LCD_CHAR_WIDTH; ++i) {
        spi_send(page_str[i]);
    }

    NHD_LCD_REG_SEL_LOW;
    SPI_SS_DESELECT;
}

void nhd_lcd_create_centered_str(char* in_str, uint8_t in_str_len, char* out_str) {
    
    uint8_t padding = (NHD_LCD_NUM_CHARS_PER_LINE - in_str_len) / 2;

    memset(out_str, ' ', NHD_LCD_NUM_CHARS_PER_LINE);

    uint8_t j = 0;
    for (uint8_t i = padding; i < padding+in_str_len; ++i) {
        out_str[i] = in_str[j++];
    }

}

