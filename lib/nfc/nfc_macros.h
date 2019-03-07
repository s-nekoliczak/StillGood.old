
//
// Checksum macros
//
#define UNSIGNED_CHAR_SIZE              256
#define DCS_MASK                        0x100

#define LOGICAL_TARGET                  0x01
#define BAUD_MOD_TYPE                   0x00


//
// PN532 command macros
//
#define CMD_PREAMBLE                    0x00
#define CMD_START_0                     0x00
#define CMD_START_1                     0xFF
#define CMD_TFI_SEND                    0xD4
#define CMD_TFI_RCV                     0xD5
#define CMD_POSTAMBLE                   0x00
#define CMD_RCV_SUCCESS                 0x00

//
// SAMConfiguration macros
//
#define WAKEUP_CMD                      0x14
#define WAKEUP_CMD_SIZE                 10
#define WAKEUP_DATA_SIZE                2
#define WAKEUP_SUCCESS_CODE             0x15
#define WAKEUP_NORMAL_MODE              0x01

//
// InListPassiveTarget macros
//
#define LIST_CMD                        0x4A
#define LIST_CMD_SIZE                   11
#define LIST_DATA_SIZE                  3
#define LIST_SUCCESS_CODE               0x4B
#define LIST_UID_SIZE                   4
#define LIST_UID_OFFSET                 7   // Offset from success code index
                                            // to UID index.

//
// InDataExchange macros
//

// Authenticate 
#define AUTH_CMD                        0x40
#define AUTH_CMD_SIZE                   22
#define AUTH_DATA_SIZE                  14
#define AUTH_MIFARE_CMD                 0x60
#define AUTH_MIFARE_ADDR                0x07
#define AUTH_SUCCESS_CODE               0x41

// Read
#define READ_CMD                        0x40
#define READ_CMD_SIZE                   12
#define READ_DATA_SIZE                  4
#define READ_SUCCESS_CODE               0x41
#define READ_MIFARE_CMD                 0x30
#define READ_PAYLOAD_SIZE               16
#define READ_PAYLOAD_OFFSET             2   // Offset from success code index
                                            // to payload index.

// WRITE
#define WRITE_CMD                       0x40
#define WRITE_CMD_SIZE                  28
#define WRITE_DATA_SIZE                 20
#define WRITE_SUCCESS_CODE              0x41
#define WRITE_MIFARE_CMD                0xA0
#define WRITE_PAYLOAD_SIZE              16

