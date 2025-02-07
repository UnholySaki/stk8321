#ifndef STK8321_H
#define STK8321_H


#include <stdint.h>

void stk8321_set_spi_spec(struct spi_dt_spec spispec);
void stk8321_read_chip_id(void);

#endif