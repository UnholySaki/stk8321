/*
 * Copyright (c) 2024 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/sys/printk.h>

/* STEP 1.2 - Include the header files for SPI, GPIO and devicetree */
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/spi.h>

#include "../inc/main.h"
#include "../inc/stk8321.h"
#include "../inc/stk8321_spi.h"

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
	uint16_t accel_x, accel_y, accel_z;
	peripheral_init();

	stk8321_set_spi_spec(spispec);
	stk8321_init();
	stk8321_read_chip_id();

	printk("Hello World! %s\n", CONFIG_BOARD);

	while (1)
	{
		/**
		 * The output will be ranging from 0 to 4
		 * 0 or 4 means the acceleration is 0
		 * 1 or 3 means the acceleration is +1g or -1g
		 * 2 means the acceleration is +-2g
		 */
		accel_x = stk8321_read_accel_x();
		printk("Accel X: %.4f\n", (float) accel_x / 1024);

		accel_y = stk8321_read_accel_y();
		printk("Accel Y: %.4f\n", (float) accel_y / 1024);

		accel_z = stk8321_read_accel_z();
		printk("Accel Z: %.4f\n", (float) accel_z / 1024);

		gpio_pin_toggle_dt(&ledspec);
		k_msleep(DELAY_VALUES);
	}

	return 0;
}
