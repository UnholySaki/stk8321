#include "../inc/stk8321_spi.h"

#include <zephyr/kernel.h>
#include <zephyr/drivers/spi.h>

static struct spi_dt_spec spi_spec;

void stk8321_set_spi_spec(void *spispec)
{
    struct spi_dt_spec _spispec = *(struct spi_dt_spec*)spispec;
    spi_spec = _spispec;
}

int stk8321_read_reg(uint8_t reg, uint8_t *data, uint8_t size)
{
    int err;

    uint8_t tx_buffer = reg | 0x80;
    struct spi_buf tx_spi_buf = {.buf = (void *)&tx_buffer, .len = 1};
    struct spi_buf_set tx_spi_buf_set = {.buffers = &tx_spi_buf, .count = 1};
    struct spi_buf rx_spi_bufs = {.buf = data, .len = size};
    struct spi_buf_set rx_spi_buf_set = {.buffers = &rx_spi_bufs, .count = 1};

    err = spi_transceive_dt(&spi_spec, &tx_spi_buf_set, &rx_spi_buf_set);
    if (err < 0)
    {

        return err;
    }

    return 0;
}

int stk8321_write_reg(uint8_t reg, uint8_t value)
{
    int err;

    uint8_t tx_buf[] = {(reg), value};
    struct spi_buf tx_spi_buf = {.buf = tx_buf, .len = sizeof(tx_buf)};
    struct spi_buf_set tx_spi_buf_set = {.buffers = &tx_spi_buf, .count = 1};

    err = spi_write_dt(&spi_spec, &tx_spi_buf_set);
    if (err < 0)
    {

        return err;
    }

    return 0;
}
