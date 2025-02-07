/**
 * @file stk8321_registers.h
 * @brief STK8321 register definitions
 * @date 2025-02-07
 */

#ifndef STK8321_REGISTERS_H
#define STK8321_REGISTERS_H

#define REG_CHIP_ID 0x00
#define REG_CHIP_ID_VALUE 0x21

#define REG_CTRL1 0x10
#define REG_CTRL1_DEFAULT 0x00

#define REG_CTRL2 0x11
#define REG_CTRL2_DEFAULT 0x00

#define REG_CTRL3 0x12
#define REG_CTRL3_DEFAULT 0x00

#define REG_INT_CTRL 0x13
#define REG_INT_CTRL_DEFAULT 0x00

#define REG_DATA_X_LSB 0x20
#define REG_DATA_X_MSB 0x21
#define REG_DATA_Y_LSB 0x22
#define REG_DATA_Y_MSB 0x23
#define REG_DATA_Z_LSB 0x24
#define REG_DATA_Z_MSB 0x25

// Additional registers
#define REG_STATUS 0x27
#define REG_STATUS_DEFAULT 0x00

#define REG_FIFO_CTRL 0x2E
#define REG_FIFO_CTRL_DEFAULT 0x00

#define REG_FIFO_DATA 0x2F

#define REG_INT_STATUS 0x30
#define REG_INT_STATUS_DEFAULT 0x00

#define REG_TEMP_LSB 0x31
#define REG_TEMP_MSB 0x32

#define REG_SOFT_RESET 0x3F
#define REG_SOFT_RESET_VALUE 0xB6

#endif // STK8321_REGISTERS_H