#ifndef STK8321_SPI_H
#define STK8321_SPI_H

#include <stdint.h>

/* Define the operating system or platform */
#define ZEPHYR_OS

/* Uncomment the following line if using Arduino ESP32 */
// #define ARDUINO_ESP32

/* Uncomment the following line if using STM32 */
// #define STM32

/* Ensure only one platform is defined */
#if defined(ZEPHYR_OS) && (defined(ARDUINO_ESP32) || defined(STM32))
#error "Multiple platforms defined. Please define only one platform."
#elif defined(ARDUINO_ESP32) && defined(STM32)
#error "Multiple platforms defined. Please define only one platform."
#elif !defined(ZEPHYR_OS) && !defined(ARDUINO_ESP32) && !defined(STM32)
#error "No platform defined. Please define one platform."
#endif

/* device specific */
void stk8321_set_spi_spec(struct spi_dt_spec spispec);

/* common */
int stk8321_read_reg(uint8_t reg, uint8_t *data, uint8_t size);
int stk8321_write_reg(uint8_t reg, uint8_t value);

#endif // STK8321_SPI_H