
/*
TXD is orange
RXD is yellow
*/

#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include <uart.h>
#include <nfc_macros.h>


unsigned char __g_uid[4];

unsigned char __calc_dcs(unsigned char tfi, unsigned char* data, uint8_t tfi_data_len) {

    uint16_t sum = 0;

    sum += (uint8_t)tfi;
    for (uint8_t i = 0; i < tfi_data_len-1; ++i) {
        sum += (uint8_t)data[i];
    }

    sum %= DCS_MASK;

    return (DCS_MASK - sum);
}

unsigned char __calc_lcs(unsigned char len) {
    return (unsigned char)(UNSIGNED_CHAR_SIZE - (uint8_t)len);
}


// cmd must be +1 char longer to account for \0 at the end.
void __build_cmd(unsigned char* cmd, unsigned char tfi, unsigned char* data, uint8_t tfi_data_len) {

    uint8_t i = 0;
    cmd[i++] = CMD_PREAMBLE;
    cmd[i++] = CMD_START_0;
    cmd[i++] = CMD_START_1;

    cmd[i++] = tfi_data_len;
    cmd[i++] = __calc_lcs(tfi_data_len);

    cmd[i++] = tfi;
    for (uint8_t j = 0; j < tfi_data_len-1; ++j) {
        cmd[i++] = data[j];
    }

    cmd[i++] = __calc_dcs(tfi, data, tfi_data_len);
    cmd[i++] = CMD_POSTAMBLE;
    cmd[i++] = '\0';
}

// Returns index of success value in buf.
uint8_t __is_reply_successful(unsigned char* buf, uint16_t len, unsigned char success_code, uint8_t check_status) {
    for (uint16_t i = 0; i < len; ++i) {
        if (buf[i] == CMD_TFI_RCV) {
            if (buf[i+1] == success_code) {
                if (check_status) {
                    if (buf[i+2] == CMD_RCV_SUCCESS) {
                        return i+1;
                    } else {
                        return 0;
                    }
                } else {
                    return i+1;
                }
            }
        }
    }

    return 0;
}


uint8_t wakeup() {

    /*
    unsigned char cmd[WAKEUP_CMD_SIZE] = "";
    unsigned char data[WAKEUP_DATA_SIZE] = "";

    uint8_t i = 0;
    data[i++] = WAKEUP_CMD;
    data[i++] = WAKEUP_NORMAL_MODE;

    __build_cmd(cmd, CMD_TFI_SEND, data, WAKEUP_DATA_SIZE+1);
    */

    // TODO Leave this hardcoded for now.
    // Figure out how to add 0x55 dummy bytes.
    unsigned char cmd[24] = {0x55, 0x55, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x03, 0xfd, 0xd4, 0x14, 0x01, 0x17, 0x00};

    // TODO Commenting out for hardcoded version.
    // uart_transmit_string(cmd, WAKEUP_CMD_SIZE);
    uart_transmit_string(cmd, 24);
    uart_wait_for_reply();
    unsigned char rep[WAKEUP_REPLY_MAX_SIZE];
    uint16_t rep_len = uart_copy_clear(rep);

    uint8_t retval = 0;
    if (__is_reply_successful(rep, rep_len, WAKEUP_SUCCESS_CODE, 0)) {
        retval = 1;
    }

    return retval;
}

uint8_t inlistpsvtarget() {
    unsigned char cmd[LIST_CMD_SIZE] = "";
    unsigned char data[LIST_DATA_SIZE] = "";

    uint8_t i = 0;
    data[i++] = LIST_CMD;
    data[i++] = LOGICAL_TARGET;
    data[i++] = BAUD_MOD_TYPE;

    __build_cmd(cmd, CMD_TFI_SEND, data, LIST_DATA_SIZE+1);

    uart_transmit_string(cmd, LIST_CMD_SIZE);
    uart_wait_for_reply();

    unsigned char rep[LIST_REPLY_MAX_SIZE];
    uint16_t rep_len = uart_copy_clear(rep);

    uint8_t retval = 0;
    uint8_t rep_idx = 0;
    if ((rep_idx = __is_reply_successful(rep, rep_len, LIST_SUCCESS_CODE, 0))) {
        retval = 1;

        i = 0;
        uint8_t uid_idx = rep_idx + LIST_UID_OFFSET;
        for (uint8_t j = uid_idx; j < uid_idx+LIST_UID_SIZE; ++j) {
            __g_uid[i++] = rep[j];
        }
    }

    return retval;
}

uint8_t authenticate() {
    unsigned char cmd[AUTH_CMD_SIZE];
    unsigned char data[AUTH_DATA_SIZE];

    uint8_t i = 0;
    data[i++] = AUTH_CMD;
    data[i++] = LOGICAL_TARGET;

    data[i++] = AUTH_MIFARE_CMD;

    // TODO Not sure what's going on with this, but clean it up somehow.
    data[i++] = AUTH_MIFARE_ADDR;
    uint8_t j = 0;
    for (j = 0; j < 6; ++j) {
        data[i++] = 0xFF;
    }

    for (j = 0; j < LIST_UID_SIZE; ++j) {
        data[i++] = __g_uid[j];
    }

    __build_cmd(cmd, CMD_TFI_SEND, data, AUTH_DATA_SIZE+1);

    uart_transmit_string(cmd, AUTH_CMD_SIZE);
    uart_wait_for_reply();
    unsigned char rep[AUTH_REPLY_MAX_SIZE];
    uint16_t rep_len = uart_copy_clear(rep);

    uint8_t retval = 0;
    if (__is_reply_successful(rep, rep_len, AUTH_SUCCESS_CODE, 1)) {
        retval = 1;
    }

    return retval;
}

uint8_t read_block(unsigned char* payload, unsigned char addr) {
    unsigned char cmd[READ_CMD_SIZE];
    unsigned char data[READ_DATA_SIZE];

    uint8_t i = 0;
    data[i++] = READ_CMD;
    data[i++] = LOGICAL_TARGET;
    data[i++] = READ_MIFARE_CMD;
    data[i++] = addr;

    __build_cmd(cmd, CMD_TFI_SEND, data, READ_DATA_SIZE+1);

    uart_transmit_string(cmd, READ_CMD_SIZE);
    uart_wait_for_reply();
    unsigned char rep[READ_REPLY_MAX_SIZE];
    uint16_t rep_len = uart_copy_clear(rep);

    uint8_t retval = 0;
    uint8_t rep_idx = 0;
    if ((rep_idx = __is_reply_successful(rep, rep_len, READ_SUCCESS_CODE, 1))) {
        retval = 1;

        i = 0;
        uint8_t uid_idx = rep_idx + READ_PAYLOAD_OFFSET;
        for (uint8_t j = uid_idx; j < uid_idx+READ_PAYLOAD_SIZE; ++j) {
            payload[i++] = rep[j];
        }
    }

    return retval;
}

uint8_t write_block(unsigned char* payload, unsigned char addr) {
    unsigned char cmd[WRITE_CMD_SIZE];
    unsigned char data[WRITE_DATA_SIZE];

    uint8_t i = 0;
    data[i++] = WRITE_CMD;
    data[i++] = LOGICAL_TARGET;
    data[i++] = WRITE_MIFARE_CMD;
    data[i++] = addr;

    for (uint8_t j = 0; j < WRITE_PAYLOAD_SIZE; ++j) {
        data[i++] = payload[j];
    }

    __build_cmd(cmd, CMD_TFI_SEND, data, WRITE_DATA_SIZE+1);

    uart_transmit_string(cmd, WRITE_CMD_SIZE);
    uart_wait_for_reply();
    unsigned char rep[WRITE_REPLY_MAX_SIZE];
    uint16_t rep_len = uart_copy_clear(rep);

    uint8_t retval = 0;
    if (__is_reply_successful(rep, rep_len, WRITE_SUCCESS_CODE, 1)) {
        retval = 1;
    }

    return retval;
}

