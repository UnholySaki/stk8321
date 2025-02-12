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
#include "../inc/stk8321_registers.h"

const struct gpio_dt_spec led_spec = GPIO_DT_SPEC_GET(DT_NODELABEL(led0), gpios);
const struct gpio_dt_spec intpin_spec = GPIO_DT_SPEC_GET(DT_NODELABEL(intpin1), gpios);

/* STEP 3 - Retrieve the API-device structure */
#define SPIOP SPI_WORD_SET(8) | SPI_TRANSFER_MSB
struct spi_dt_spec spispec = SPI_DT_SPEC_GET(DT_NODELABEL(stk8321), SPIOP, 0);

static struct gpio_callback intpin_cb_data;

void intpin_triggered(const struct device *dev, struct gpio_callback *cb,
					  uint32_t pins)
{
	printk("Button pressed at %" PRIu32 "\n", k_cycle_get_32());
}

static int int_pin_init(void)
{
	int ret;
	if (!gpio_is_ready_dt(&intpin_spec))
	{
		return 0;
	}

	ret = gpio_pin_configure_dt(&intpin_spec, GPIO_INPUT);
	if (ret != 0)
	{
		return 0;
	}

	ret = gpio_pin_interrupt_configure_dt(&intpin_spec,
										  GPIO_INT_EDGE_TO_ACTIVE);
	if (ret != 0)
	{
		return 0;
	}

	gpio_init_callback(&intpin_cb_data, intpin_triggered, BIT(intpin_spec.pin));
	gpio_add_callback(intpin_spec.port, &intpin_cb_data);
	printk("Set up intpin at %s pin %d\n", intpin_spec.port->name, intpin_spec.pin);
	return 0;
}
static int peripheral_init(void)
{
	int err;

	err = spi_is_ready_dt(&spispec);
	if (!err)
	{
		return 0;
	}

	if (!gpio_is_ready_dt(&led_spec))
		return false;

	if (gpio_pin_configure_dt(&led_spec, GPIO_OUTPUT_INACTIVE) < 0)
		return false;

	int_pin_init();

	return 0;
}

int main(void)
{
	uint16_t accel_x, accel_y, accel_z;
	peripheral_init();

	stk8321_set_spi_spec(spispec);
	stk8321_init(DEF_RANGE, DEF_BW);
	uint16_t chip_id = stk8321_read_chip_id();

	printk("Hello World! %s (id#%d)\n", CONFIG_BOARD, chip_id);

	while (1)
	{
		/**
		 * The output will be ranging from 0 to 4
		 * 0 or 4 means the acceleration is 0
		 * 1 or 3 means the acceleration is +1g or -1g
		 * 2 means the acceleration is +-2g
		 */
		accel_x = stk8321_read_accel_x();
		accel_y = stk8321_read_accel_y();
		accel_z = stk8321_read_accel_z();
		printk("Accel values: X: %.2f, Y: %.2f, Z: %.2f\n",
			   ((double)accel_x) / 1024,
			   ((double)accel_y) / 1024,
			   ((double)accel_z) / 1024);

		uint8_t int_status = stk8321_read_int_sts();
		if (int_status & SIG_MOT_STS_BIT)
		{
			printk("Significant motion detected\n");
		}
		else if (int_status & ANY_MOT_STS_BIT)
		{
			printk("Any motion detected\n");
		}

		gpio_pin_toggle_dt(&led_spec);
		k_msleep(DELAY_VALUES);
	}

	return 0;
}
