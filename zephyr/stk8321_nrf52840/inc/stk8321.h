#ifndef STK8321_H
#define STK8321_H


#include <stdint.h>


void stk8321_init(void);

/*========= SETUP FUNCTIONS ===========*/
void stk8321_pwr_mode_set(uint8_t mode);
void stk8321_set_range(uint8_t range);
void stk8321_set_bandwidth(uint8_t bandwidth);
void stk8321_set_offset_x(uint8_t offset);
void stk8321_set_offset_y(uint8_t offset);
void stk8321_set_offset_z(uint8_t offset);
void stk8321_reset_offset(void);

/*========= GET DATA FUNCTIONAS ==========*/
void stk8321_read_chip_id(void);

uint16_t stk8321_read_accel_x(void);
uint16_t stk8321_read_accel_y(void);
uint16_t stk8321_read_accel_z(void);

#endif // STK8321_H