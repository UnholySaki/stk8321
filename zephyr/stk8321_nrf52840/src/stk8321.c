/**
 * @file stk8321.c
 * @brief STK8321 driver implementation
 * @date 2025/02/07
 *
 * @note This file is used to implement the STK8321 driver
 * @author
 */

#include "../inc/stk8321.h"
#include "../inc/stk8321_spi.h"
#include "../inc/stk8321_registers.h"

static uint8_t cur_pow_state = POWMODE_ACTIVE;

void stk8321_init(void)
{
    stk8321_pwr_mode_set(POWMODE_SUSPEND);

    stk8321_set_range(RANGE_2G);
    stk8321_set_bandwidth(BW_31_25_HZ);
    stk8321_reset_offset();

    stk8321_pwr_mode_set(POWMODE_ACTIVE);
}

void stk8321_pwr_mode_set(uint8_t power_mode)
{
    if (power_mode == cur_pow_state)
    {
        return;
    }
    cur_pow_state = power_mode;
    stk8321_write_reg(REG_POWMODE, power_mode);
}

void stk8321_set_range(uint8_t range)
{
    stk8321_pwr_mode_set(POWMODE_SUSPEND);
    stk8321_write_reg(REG_RANGESEL, range);
    stk8321_pwr_mode_set(POWMODE_ACTIVE);
}

void stk8321_set_bandwidth(uint8_t bandwidth)
{
    stk8321_pwr_mode_set(POWMODE_SUSPEND);
    stk8321_write_reg(REG_BANDWIDTHSEL, bandwidth);
    stk8321_pwr_mode_set(POWMODE_ACTIVE);
}

void stk8321_set_offset(uint8_t x_offset, uint8_t y_offset, uint8_t z_offset)
{
    stk8321_write_reg(REG_OFST_X, x_offset);
    stk8321_write_reg(REG_OFST_Y, y_offset);
    stk8321_write_reg(REG_OFST_Z, z_offset);
}

void stk8321_reset_offset(void)
{
    stk8321_write_reg(REG_OFST_RESET, 0x01);
}

void stk8321_set_int1_map(uint8_t value)
{
    stk8321_write_reg(REG_INT_MAP_1, value);
}

/*============= GET DATA FUNCTIONS ================*/
uint8_t stk8321_read_chip_id(void)
{
    uint8_t size = 2;
    uint8_t values[size];
    stk8321_read_reg(REG_CHIP_ID, values, size);
    return values[1];
}

uint16_t stk8321_read_accel_x(void)
{
    uint8_t size = 2;
    uint8_t values[size];
    uint16_t lsb_val, msb_val;

    stk8321_read_reg(REG_DATA_X_LSB, values, size);
    lsb_val = values[1] >> 4;
    stk8321_read_reg(REG_DATA_X_MSB, values, size);
    msb_val = values[1];
    return (msb_val << 4) | lsb_val;
}

uint16_t stk8321_read_accel_y(void)
{
    uint8_t size = 2;
    uint8_t values[size];
    uint16_t lsb_val, msb_val;

    stk8321_read_reg(REG_DATA_Y_LSB, values, size);
    lsb_val = values[1] >> 4;
    stk8321_read_reg(REG_DATA_Y_MSB, values, size);
    msb_val = values[1];
    return (msb_val << 4) | lsb_val;
}

uint16_t stk8321_read_accel_z(void)
{
    uint8_t size = 2;
    uint8_t values[size];
    uint16_t lsb_val, msb_val;

    stk8321_read_reg(REG_DATA_Z_LSB, values, size);
    lsb_val = values[1] >> 4;
    stk8321_read_reg(REG_DATA_Z_MSB, values, size);
    msb_val = values[1];
    return (msb_val << 4) | lsb_val;
}
