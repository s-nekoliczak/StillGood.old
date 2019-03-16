
#include <stdio.h>
#include <i2c.h>

#define RTC_I2C_ADDR        0x68

#define RTC_YEAR_BIAS       2000

// RTC internal addresses
#define RTC_ADDR_SECS       0x00
#define RTC_ADDR_MINUTE     0x01
#define RTC_ADDR_HOURS      0x02
#define RTC_ADDR_DAYS       0x03
#define RTC_ADDR_DATE       0x04
#define RTC_ADDR_MONTH      0x05
#define RTC_ADDR_YEAR       0x06
#define RTC_ADDR_CONTROL    0x07

// Master transmitter error codes: pg 273, table 26-3
#define RTC_MSTR_TRANS_START            0x08
#define RTC_MSTR_TRANS_RPTD_START       0x10
#define RTC_MSTR_TRANS_SLA_W_ACK        0x18
#define RTC_MSTR_TRANS_SLA_W_NACK       0x20
#define RTC_MSTR_TRANS_SEND_BYTE_ACK    0x28
#define RTC_MSTR_TRANS_SEND_BYTE_NACK   0x30
#define RTC_MSTR_TRANS_ARB_LOST         0x38

// Error codes: pg 277, table 26-4
#define RTC_MSTR_RCV_START              0x08
#define RTC_MSTR_RCV_RPTD_START         0x10
#define RTC_MSTR_RCV_ARB_LOST           0x38
#define RTC_MSTR_RCV_SLA_R_ACK          0x40
#define RTC_MSTR_RCV_SLA_R_NACK         0x48
#define RTC_MSTR_RCV_RCV_BYTE_ACK       0x50
#define RTC_MSTR_RCV_RCV_BYTE_NACK      0x58


uint8_t rtc_send_data(uint8_t addr, uint8_t* data, uint8_t data_len,
                                uint8_t is_stop) {

    uint8_t st = i2c_start_trans();

    if (st != RTC_MSTR_TRANS_START && st != RTC_MSTR_TRANS_RPTD_START) {
        i2c_stop_send();
        return st;
    }

    st = i2c_send_addr(RTC_I2C_ADDR, 0);
    if (st != RTC_MSTR_TRANS_SLA_W_ACK) {
        i2c_stop_send();
        return st;
    }

    st = i2c_send_dbyte(addr);
    if (st != RTC_MSTR_TRANS_SEND_BYTE_ACK) {
        i2c_stop_send();
        return st;
    }

    for (uint16_t i = 0; i < data_len; ++i) {
        st = i2c_send_dbyte(data[i]);
        if (st != RTC_MSTR_TRANS_SEND_BYTE_ACK) {
            i2c_stop_send();
            return st;
        }
    }

    if (is_stop == 1) {
        i2c_stop_send();
    }

    return st;
}


uint8_t rtc_rcv_data(uint8_t addr, uint8_t* data, uint8_t data_len, uint8_t is_stop) {

    rtc_send_data(addr, 0, 0, 0);

    uint8_t st = i2c_start_trans();
    if (st != RTC_MSTR_RCV_START && st != RTC_MSTR_RCV_RPTD_START) {
        i2c_stop_send();
        return st;
    }

    st = i2c_send_addr(RTC_I2C_ADDR, 1);
    if (st != RTC_MSTR_RCV_SLA_R_ACK) {
        i2c_stop_send();
        return st;
    }

    for (uint8_t i = 0; i < data_len; ++i) {
        st = i2c_rcv_dbyte();
        if (st == RTC_MSTR_RCV_RCV_BYTE_ACK) {
            data[i] = i2c_read_data();
        } else {
            i2c_stop_rcv();
            return st;
        }
    }
    
    if (is_stop == 1) {
        i2c_stop_rcv();
    }

    return st;
}

uint16_t rtc_rtcyear_to_year(uint8_t rtcyear) {
    return ((RTC_YEAR_BIAS + ((rtcyear & 0xF0) >> 4) * 10) + (rtcyear & 0x0F));
}

uint8_t rtc_year_to_rtcyear(uint16_t year) {
    return ((((year - RTC_YEAR_BIAS) / 10) << 4) | ((year - RTC_YEAR_BIAS) % 10));

}

uint8_t rtc_set_year(uint16_t year) {
    uint8_t year_arr[1] = { rtc_year_to_rtcyear(year) };

    return rtc_send_data(RTC_ADDR_YEAR, year_arr, 1, 1);
}

uint16_t rtc_get_year() {
    uint8_t rtcyear_arr[1];
    uint8_t st = rtc_rcv_data(RTC_ADDR_YEAR, rtcyear_arr, 1, 1);
    if (st != RTC_MSTR_RCV_RCV_BYTE_ACK) {
        return 0;
    }

    return rtc_rtcyear_to_year(rtcyear_arr[0]);
}

