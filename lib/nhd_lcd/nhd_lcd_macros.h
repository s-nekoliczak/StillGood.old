
//
// Commands
//

#define NHD_LCD_CHAR_WIDTH              6

#define NHD_LCD_CMD_RESET               0b11100010

#define NHD_LCD_CMD_DISP_ALL            0b10100101
#define NHD_LCD_CMD_DISP_NORMAL         0b10100100

// Init commands
#define NHD_LCD_ADC_NORM                0xA0
#define NHD_LCD_CMD_DISP_OFF            0xAE
#define NHD_LCD_CMD_DISP_ON             0xAF
#define NHD_LCD_OUTPUT_MODE_REV         0xC0
#define NHD_LCD_BIAS_1_9                0xA2
#define NHD_LCD_PWR_CTRL_SET_DEFAULT    0x2F
#define NHD_LCD_RESIST_RATIO_DEFAULT    0x26
#define NHD_LCD_ELEC_VOL_DEFAULT        0x81
#define NHD_LCD_STATIC_IND_OFF          0xAC
#define NHD_LCD_STATIC_IND_ON           0xAD
#define NHD_LCD_ALL_POINTS_NORMAL       0xA4
#define NHD_LCD_ALL_POINTS_ON           0xA5


//
// Sizes
//

#define NHD_LCD_PAGE_COLS_SIZE          0x84
#define NHD_LCD_NUM_PAGES               8
#define NHD_LCD_NUM_CHARS_PER_LINE      22
#define NHD_LCD_BYTE_SIZE               8

// Set the column in a row to all blank pixels
#define NHD_LCD_ROW_COL_BLANK           0x00

#define NHD_LCD_PORT                    PORTB
#define NHD_LCD_DDR                     DDRB

#define NHD_LCD_RESET                   PB0
#define NHD_LCD_REG_SEL                 PB1     // 0 instr or 1 data for A0
#define NHD_LCD_SS                      PB2
#define NHD_LCD_MOSI                    PB3
#define NHD_LCD_SCK                     PB5

#define NHD_LCD_SS_SELECT               NHD_LCD_PORT &= ~(1 << NHD_LCD_SS)
#define NHD_LCD_SS_DESELECT             NHD_LCD_PORT |= (1 << NHD_LCD_SS)

#define NHD_LCD_REG_SEL_HIGH            NHD_LCD_PORT |= (1 << NHD_LCD_REG_SEL)
#define NHD_LCD_REG_SEL_LOW             NHD_LCD_PORT &= ~(1 << NHD_LCD_REG_SEL)


#define NHD_LCD_RESET_HIGH              NHD_LCD_PORT |= (1 << NHD_LCD_RESET)
#define NHD_LCD_RESET_LOW               NHD_LCD_PORT &= ~(1 << NHD_LCD_RESET)

#define NHD_LCD_LIGHT_PORT              PORTD
#define NHD_LCD_LIGHT_DDR               DDRD

#define NHD_LCD_BL                      PD7
#define NHD_LCD_RED                     PD6
#define NHD_LCD_GREEN                   PD5
#define NHD_LCD_BLUE                    PD4

#define NHD_LCD_BL_ON                   NHD_LCD_LIGHT_PORT |= (1 << NHD_LCD_BL)
#define NHD_LCD_BL_OFF                  NHD_LCD_LIGHT_PORT &= ~(1 << NHD_LCD_BL)

#define NHD_LCD_RED_ON                  NHD_LCD_LIGHT_PORT |= (1 << NHD_LCD_RED)
#define NHD_LCD_RED_OFF                 NHD_LCD_LIGHT_PORT &= ~(1 << NHD_LCD_RED)

#define NHD_LCD_GREEN_ON                NHD_LCD_LIGHT_PORT |= (1 << NHD_LCD_GREEN)
#define NHD_LCD_GREEN_OFF               NHD_LCD_LIGHT_PORT &= ~(1 << NHD_LCD_GREEN)

#define NHD_LCD_BLUE_ON                 NHD_LCD_LIGHT_PORT |= (1 << NHD_LCD_BLUE)
#define NHD_LCD_BLUE_OFF                NHD_LCD_LIGHT_PORT &= ~(1 << NHD_LCD_BLUE)


