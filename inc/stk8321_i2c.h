#ifndef STK8321_I2C_H
#define STK8321_I2C_H

#include <stdint.h>

/* device specific */
void stk8321_set_i2c_spec(void *i2cspec);

/* common */
int stk8321_read_reg(uint8_t reg, uint8_t *data, uint8_t size);
int stk8321_write_reg(uint8_t reg, uint8_t value);

#endif // STK8321_I2C_H