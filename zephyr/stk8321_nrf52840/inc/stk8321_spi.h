#ifndef STK8321_SPI_H
#define STK8321_SPI_H

#include <stdint.h>
/* device specific */
void stk8321_set_spi_spec(struct spi_dt_spec spispec);

/* common */
int stk8321_read_reg(uint8_t reg, uint8_t *data, uint8_t size);
int stk8321_write_reg(uint8_t reg, uint8_t value);

#endif // STK8321_SPI_H