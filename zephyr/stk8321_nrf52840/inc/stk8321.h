#ifndef STK8321_H
#define STK8321_H

#include <stdint.h>
#include <stdbool.h>

typedef enum
{
    INT_PIN_1,
    INT_PIN_2
} int_pin_e;

typedef enum
{
    NONE,
    SIG_MOT,
    ANY_MOT,
    SIG_ANT_MOT,
    FIFO_FULL,
    FWM_REACHED,
    DATA_RDY,
    ALL
} int_sts_e;

typedef enum
{
    NON_LATCHED_0 = 0x0,
    TEMP_250MS = 0x1,
    TEMP_500MS = 0x2,
    TEMP_1S = 0x3,
    TEMP_2S = 0x4,
    TEMP_4S = 0x5,
    TEMP_8S = 0x6,
    LATCHED_7 = 0x7,
    NON_LATCHED_8 = 0x8,
    TEMP_250US = 0x9,
    TEMP_500US = 0xA,
    TEMP_1MS = 0xB,
    TEMP_12_5MS = 0xC,
    TEMP_25MS = 0xD,
    TEMP_50MS = 0xE,
    LATCHED_F = 0xF,
    RESET = 0x80,
} int_latch_mode_e;

/* Default values*/
#define DEF_RANGE RANGE_2G
#define DEF_BW BW_31_25_HZ

#define DEF_DATA_PROTECTED true
#define DEF_DATA_FILTERED true

#define DEF_INT_OD_MODE false
#define DEF_INT_LV_MODE true

/* Significant motion detection parameters */
#define SIG_MOT_SKIP_TIME 0x0A  // 100ms - def: 0x96 (3 seconds)
#define SIG_MOT_PROOF_TIME 0x32 // def: 0x32 (1 second)
#define SLOPE_DUR 0x00          // def: 0x00 (1 sample)
#define SLOPE_THD 0x14          // def: 0x14 (20mg)
#define SIG_MOT_INT_PIN SIG_MOT_2_INT1_BIT
#define INT_LATCH_MODE NON_LATCHED_0

/*==================== PRESET FUNCTIONS =========================*/
void stk8321_init(uint8_t range, uint8_t bw);

/**
 * @brief Configure the STK8321 to detect significant motion with default settings
 * @note for further details refer to the datasheet
 */
void stk8321_cfg_en_sig_motion(void);

/*========= SETUP FUNCTIONS ===========*/
/* REG 0x0F */
void stk8321_set_range(uint8_t range);
/* REG 0x10 */
void stk8321_set_bandwidth(uint8_t bandwidth);
/* REG 0x11 */
void stk8321_pwr_mode_set(uint8_t mode);
/* REG 0x13 */
void stk8321_cfg_data_setup(bool is_protected, bool is_filtered);
/* REG 0x14 */
void stk8321_sw_rst(void);
/* REG 0x16 */
void stk8321_cfg_en_int_1(bool en_x, bool en_y, bool en_z);
/* REG 0x19 */
void stk8321_cfg_set_int1_map(uint8_t int_mode);
/* REG 0x20 */
void stk8321_cfg_int_pin(uint8_t int_pin, bool is_open_drain, bool is_active_low);
/* REG 0x21 */
void stk8321_cfg_int_pin_latch(int_latch_mode_e mode);
/* REG 0x27 */
void stk8321_cfg_slope_dur(uint8_t dur);
/* REG 0x28 */
void stk8321_cfg_slope_thd(uint8_t thd);
/* REG 0x36 */
void stk8321_reset_offset(void);
/* REG 0x38, 0x39, 0x3A*/
void stk8321_set_offset(uint8_t x_offset, uint8_t y_offset, uint8_t z_offset);

/*========= GET DATA FUNCTIONAS ==========*/
/* REG 0x00 -  Read chip identification code, expecting - 0x23. */
uint8_t stk8321_read_chip_id(void);
/* REG 0x02, 0x03 - Read x-axis acceleration data */
uint16_t stk8321_read_accel_x(void);
/* REG 0x04, 0x05 - Read y-axis acceleration data */
uint16_t stk8321_read_accel_y(void);
/* REG 0x06, 0x07 - Read z-axis acceleration data */
uint16_t stk8321_read_accel_z(void);
/**
 * @brief Read motion and data interrupts status
 * @note if bit n is set, the interrupt n is active
 *       bit 0 - significant motion
 *       bit 2 - any motion
 *       bit 5 - FIFO full
 *       bit 6 - FIFO watermark reached
 *       bit 7 - new data ready
 * @return uint8_t - interrupt status
 */
uint8_t stk8321_read_int_sts(void);
/* REG 0x0C */
uint8_t stk8321_read_fifo_sts(void);

#endif // STK8321_H