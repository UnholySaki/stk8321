/*
 * Copyright (c) 2024 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

/* STEP 1.2 - Include the header files for SPI, GPIO and devicetree */
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/spi.h>

#include "../inc/main.h"
#include "../inc/stk8321.h"

const struct gpio_dt_spec ledspec = GPIO_DT_SPEC_GET(DT_NODELABEL(led0), gpios);

/* STEP 3 - Retrieve the API-device structure */
#define SPIOP SPI_WORD_SET(8) | SPI_TRANSFER_MSB
struct spi_dt_spec spispec = SPI_DT_SPEC_GET(DT_NODELABEL(bme280), SPIOP, 0);

static int peripheral_init(void)
{
	int err;

	err = spi_is_ready_dt(&spispec);
	if (!err)
	{
		return 0;
	}

	if (!gpio_is_ready_dt(&ledspec))
		return false;

	if (gpio_pin_configure_dt(&ledspec, GPIO_OUTPUT_INACTIVE) < 0)
		return false;

	return 0;
}

int main(void)
{
	peripheral_init();

	stk8321_set_spi_spec(spispec);
	stk8321_read_chip_id();

	while (1)
	{
		gpio_pin_toggle_dt(&ledspec);
		k_msleep(DELAY_VALUES);
	}

	return 0;
}
