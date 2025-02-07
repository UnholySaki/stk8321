/**
 * @file stk8321.c
 * @brief STK8321 driver implementation
 * @date 2025/02/07
 * 
 * @note This file is used to implement the STK8321 driver
 * @author 
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/spi.h>

#include "../inc/stk8321.h"
#include "../inc/stk8321_registers.h"

static struct spi_dt_spec spi_spec;

void stk8321_set_spi_spec(struct spi_dt_spec spispec)
{
    spi_spec = spispec;
}

static int stk8321_read_reg(uint8_t reg, uint8_t *data, uint8_t size)
{
    int err;

    /* STEP 4.1 - Set the transmit and receive buffers */
    uint8_t tx_buffer = reg | 0x80;
    struct spi_buf tx_spi_buf = {.buf = (void *)&tx_buffer, .len = 1};
    struct spi_buf_set tx_spi_buf_set = {.buffers = &tx_spi_buf, .count = 1};
    struct spi_buf rx_spi_bufs = {.buf = data, .len = size};
    struct spi_buf_set rx_spi_buf_set = {.buffers = &rx_spi_bufs, .count = 1};

    /* STEP 4.2 - Call the transceive function */
    err = spi_transceive_dt(&spi_spec, &tx_spi_buf_set, &rx_spi_buf_set);
    if (err < 0)
    {

        return err;
    }

    return 0;
}

static int stk8321_write_reg(uint8_t reg, uint8_t value)
{
    int err;

    /* STEP 5.1 - declare a tx buffer having register address and data */
    uint8_t tx_buf[] = {(reg), value};
    struct spi_buf tx_spi_buf = {.buf = tx_buf, .len = sizeof(tx_buf)};
    struct spi_buf_set tx_spi_buf_set = {.buffers = &tx_spi_buf, .count = 1};

    /* STEP 5.2 - call the spi_write_dt function with SPISPEC to write buffers */
    err = spi_write_dt(&spi_spec, &tx_spi_buf_set);
    if (err < 0)
    {

        return err;
    }

    return 0;
}

void stk8321_read_chip_id(void)
{
    uint8_t _size = 2;
    uint8_t _values[_size];
    stk8321_read_reg(REG_CHIP_ID, _values, _size);
}


void stk8321_read_accel_x(void) {
    uint8_t _size = 2;
    uint8_t _values[_size];
    stk8321_read_reg(REG_DATA_X_LSB, _values, _size);

    stk8321_read_reg(REG_DATA_X_MSB, _values + 1, _size);
}