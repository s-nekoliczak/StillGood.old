
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uart.h>
#include <util/delay.h>

#define BT_CMD_INIT                 "$$$"
#define BT_CMD_KILL                 "---"
#define BT_CMD_FACTORY_DEFAULT      "SF,1"
#define BT_CMD_SET_MODE             "SM,"

#define BT_CMD_SET_DEVICE_NAME      "SN,"
#define BT_CMD_SET_SERIAL_NAME      "S-,"

#define BT_CMD_SET_PIN              "SP,"

#define BT_CMD_POWER_CYCLE          "R,1"

void __bt_transmit(char* str) {
    uart_transmit_string((unsigned char*) str, strlen(str));
}

void __bt_cmd_transmit(char* cmd, char* arg) {
    
    // +2 for \r and \0
    uint8_t len = strlen(cmd) + strlen(arg) + 2;
    char* cmd_str = (char*)calloc(len, sizeof(char));

    // \0 is implied in snprintf
    if (arg == 0) {
        snprintf(cmd_str, len, "%s\r", cmd);
    } else {
        snprintf(cmd_str, len, "%s%s\r", cmd, arg);
    }

    __bt_transmit(cmd_str);

    free(cmd_str);
}

void bt_cmd_init() {
    __bt_transmit(BT_CMD_INIT);
}

void bt_cmd_kill() {
    __bt_cmd_transmit(BT_CMD_KILL, 0);
}

void bt_cmd_factory_default() {
    __bt_cmd_transmit(BT_CMD_FACTORY_DEFAULT, 0);
}

void bt_cmd_set_mode(uint8_t mode) {

    if (mode > 6) {
        mode = 6;
    }
    
    char mode_str[1] = { mode + '0' };
    __bt_cmd_transmit(BT_CMD_SET_MODE, mode_str);
}

void bt_cmd_set_serial_name(char* name) {
    __bt_cmd_transmit(BT_CMD_SET_SERIAL_NAME, name);
}

// This sets the display name
void bt_cmd_set_device_name(char* name) {
    __bt_cmd_transmit(BT_CMD_SET_DEVICE_NAME, name);
}


/*
R,1
    forces complete device reboot (i.e. power cycle)
*/
void bt_cmd_power_cycle() {
    __bt_cmd_transmit(BT_CMD_POWER_CYCLE, 0);
}

void bt_cmd_set_pin(char* pin) {
    __bt_cmd_transmit(BT_CMD_SET_PIN, pin);
}


/*
    uint16_t rep_len = uart_rcv_buf_size();
    unsigned char* rep = (unsigned char*)calloc(rep_len, sizeof(unsigned char));
    uart_copy_clear(rep);

    uart_copy_clear(unsigned char* dest);
*/


/*
TODO

SRA - stored remote address


SP,abc
    set security pin code

SR,abc
    store SRA
    use this to pair remote/base together

SS,abc
    set service name

SU,n
    set baud rate
    default is 115200, so we're good here, but make function anyway

SW,n
    low-power sniff mode
    good for base device

SX,n
    enable/disable bonding
    uses value in SR for this

SY,n
    transmit power

S|,abc
    low-power config

C
    attempt connect to device in SRA

C,addr
    same, but to a specified address

R,1
    forces complete device reboot (i.e. power cycle)

K,
    disconnect current connection


















*/








