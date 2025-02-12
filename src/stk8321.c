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

void stk8321_init(uint8_t range, uint8_t bw)
{
    stk8321_cfg_set_pwr_mode(POWMODE_SUSPEND);

    /* Setup parameters */
    stk8321_cfg_set_range(RANGE_2G);
    stk8321_cfg_set_bandwidth(BW_31_25_HZ);
    stk8321_cfg_data_setup(DEF_DATA_PROTECTED, DEF_DATA_FILTERED);
    stk8321_rst_offset();

    /*set up interrupt pins*/
    stk8321_cfg_int_pin(INT_PIN_1, DEF_INT_OD_MODE, DEF_INT_LV_MODE); // INT1 is push-pull and active high
    
    stk8321_cfg_set_pwr_mode(POWMODE_ACTIVE);
}

void stk8321_cfg_en_sig_motion(int_pin_e int_pin, uint8_t skip_time, uint8_t proof_time, uint8_t slope_dur, uint8_t slope_thd, uint8_t latch_mode)
{
    /* Step 1: Enable sig motion specific registers*/
    stk8321_write_reg(REG_SIG_MOT_1, skip_time);
    stk8321_write_reg(REG_SIG_MOT_3, proof_time);

    stk8321_cfg_slope_dur(slope_dur);
    stk8321_cfg_slope_thd(slope_thd);
    /* Step 2: Enable slope detection*/
    stk8321_cfg_en_int_1(true, true, true);

    /* Step 3: set sig motion enabled */
    stk8321_write_reg(REG_SIG_MOT_2, SIG_MOT_EN_BIT);

    /* Step 4: map sig motion to pin 1*/
    stk8321_cfg_set_int1_map(int_pin);
    stk8321_cfg_int_pin_latch(latch_mode);

}

/*======================== SETUP FUNCTIONS ===========================*/

/* REG 0x0F */
void stk8321_cfg_set_range(uint8_t range)
{
    stk8321_cfg_set_pwr_mode(POWMODE_SUSPEND);
    stk8321_write_reg(REG_RANGESEL, range);
    stk8321_cfg_set_pwr_mode(POWMODE_ACTIVE);
}

/* REG 0x10 */
void stk8321_cfg_set_bandwidth(uint8_t bandwidth)
{
    stk8321_cfg_set_pwr_mode(POWMODE_SUSPEND);
    stk8321_write_reg(REG_BANDWIDTHSEL, bandwidth);
    stk8321_cfg_set_pwr_mode(POWMODE_ACTIVE);
}

/* REG 0x11 */
void stk8321_cfg_set_pwr_mode(uint8_t power_mode)
{
    if (power_mode == cur_pow_state)
    {
        return;
    }
    cur_pow_state = power_mode;
    stk8321_write_reg(REG_POWMODE, power_mode);
}

/* REG 0x13 */
void stk8321_cfg_data_setup(bool is_protected, bool is_filtered)
{
    uint8_t config = 0;
    if (!is_protected)
    {
        config |= DAT_PROT_BIT;
    }
    if (!is_filtered)
    {
        config |= DAT_FILT_BIT;
    }
    stk8321_write_reg(REG_DAT_SETUP, config);
}
/* REG 0x14 */
void stk8321_sw_rst(void)
{
    stk8321_write_reg(REG_SW_RST, HARD_RST_VAL);
}

/* REG 0x16 */
void stk8321_cfg_en_int_1(bool en_x, bool en_y, bool en_z)
{
    uint8_t config = 0;
    if (en_x)
    {
        config |= SLP_EN_X_BIT;
    }
    if (en_y)
    {
        config |= SLP_EN_Y_BIT;
    }
    if (en_z)
    {
        config |= SLP_EN_Z_BIT;
    }
    stk8321_write_reg(REG_INT_EN_1, config);
}

/* REG 0x19 */
void stk8321_cfg_set_int1_map(uint8_t int_mode)
{
    uint8_t mode_list[4] = {SIG_MOT_2_INT1_BIT, ANY_MOT_2_INT1_BIT,
                            ANY_MOT_2_INT2_BIT, SIG_MOT_2_INT2_BIT};
    for (int i = 0; i < sizeof(mode_list); i++)
    {
        if (int_mode == mode_list[i])
        {
            stk8321_write_reg(REG_INT_MAP_1, int_mode);
            return;
        }
    }
}

/* REG 0x20 */
void stk8321_cfg_int_pin(uint8_t int_pin, bool is_open_drain, bool is_active_low)
{
    uint8_t config = 0;
    if (int_pin != INT_PIN_1 && int_pin != INT_PIN_2)
    {
        return;
    }

    if (is_open_drain)
    {
        config |= INT1_OD_BIT;
    }

    if (is_active_low)
    {
        config |= INT1_LV_BIT;
    }

    if (int_pin == INT_PIN_2)
    {
        config <<= 2;
    }

    stk8321_write_reg(REG_INT_CFG_1, config);
}

/* REG 0x21 */
void stk8321_cfg_int_pin_latch(int_latch_mode_e mode)
{
    stk8321_write_reg(REG_INT_CFG_2, mode);
}

/* REG 0x27 */
void stk8321_cfg_slope_dur(uint8_t dur)
{
    if (dur < 0 || dur > 0x03)
        return;
    stk8321_write_reg(REG_SLOPE_DUR, dur);
}

/* REG 0x28 */
void stk8321_cfg_slope_thd(uint8_t thd)
{
    stk8321_write_reg(REG_SLOPE_DUR, thd);
}

/* REG 0x36 */
void stk8321_rst_offset(void)
{
    stk8321_write_reg(REG_OFST_RESET, 0x01);
}

/* REG 0x38, 0x39, 0x3A*/
void stk8321_cfg_set_offset(uint8_t x_offset, uint8_t y_offset, uint8_t z_offset)
{
    stk8321_write_reg(REG_OFST_X, x_offset);
    stk8321_write_reg(REG_OFST_Y, y_offset);
    stk8321_write_reg(REG_OFST_Z, z_offset);
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
/* REG 0x09, 0x0A */
uint8_t stk8321_read_int_sts(void)
{
    uint8_t size = 2;
    uint8_t values[size];
    uint8_t ret = 0x00;
    stk8321_read_reg(REG_MOT_INT_STS, values, size);
    ret |= values[1];
    stk8321_read_reg(REG_DAT_INT_STS, values, size);
    ret |= values[1];
    return ret;
}
/* REG 0x0C */
uint8_t stk8321_read_fifo_sts(void)
{
    uint8_t size = 2;
    uint8_t values[size];
    stk8321_read_reg(REG_FIFO_STS, values, size);
    return values[1];
}

/* ================*/