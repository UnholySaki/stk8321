#ifndef STK8321_H
#define STK8321_H

#include <stdint.h>
#include <stdbool.h>

typedef enum int_pin_e
{
    INT_PIN_1,
    INT_PIN_2
};

/* Significant motion detection parameters */
#define SIG_MOT_SKIP_TIME 0x0A  // 100ms - def: 0x96 (3 seconds)
#define SIG_MOT_PROOF_TIME 0x32 // def: 0x32 (1 second)
#define SLOPE_DUR 0x00          // def: 0x00 (1 sample)
#define SLOPE_THD 0x14          // def: 0x14 (20mg)
#define SIG_MOT_INT_PIN SIG_MOT_2_INT1_BIT

/*=============================================*/
void stk8321_init(void);

/**
 * @brief Configure the STK8321 to detect significant motion with default settings
 * @note for further details refer to the datasheet
 */
void stk8321_cfg_en_sig_motion(void);

/*========= SETUP FUNCTIONS ===========*/
void stk8321_pwr_mode_set(uint8_t mode);
void stk8321_set_range(uint8_t range);
void stk8321_set_bandwidth(uint8_t bandwidth);
void stk8321_set_offset_x(uint8_t offset);
void stk8321_set_offset_y(uint8_t offset);
void stk8321_set_offset_z(uint8_t offset);
void stk8321_reset_offset(void);

/* REG 0x16 */
void stk8321_cfg_en_int_1(bool en_x, bool en_y, bool en_z);

/* REG 0x19 */
void stk8321_cfg_set_int1_map(uint8_t int_mode);

/* REG 0x20 */
void stk8321_int_pin_cfg(uint8_t int_pin, bool is_open_drain, bool is_active_low);

/* REG 0x27 */
void stk8321_cfg_slope_dur(uint8_t dur);

/* REG 0x28 */
void stk8321_cfg_slope_thd(uint8_t thd);

/*========= GET DATA FUNCTIONAS ==========*/
uint8_t stk8321_read_chip_id(void);

uint16_t stk8321_read_accel_x(void);
uint16_t stk8321_read_accel_y(void);
uint16_t stk8321_read_accel_z(void);

uint8_t stk8321_read_int_status(void);
#endif // STK8321_H