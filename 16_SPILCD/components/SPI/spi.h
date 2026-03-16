#ifndef __MYSPI_H_
#define __MYSPI_H_

#include "driver/spi_master.h"

// SPI2引脚定义
#define SPI2_MISO_PIN    GPIO_NUM_13  // MISO引脚
#define SPI2_MOSI_PIN    GPIO_NUM_11  // MOSI引脚
#define SPI2_SCLK_PIN    GPIO_NUM_12  // SCLK引脚
#define SPI2_CS_PIN      GPIO_NUM_48  // CS引脚

extern spi_device_handle_t spi2_handle;

void spi2_init(void);
uint8_t spi2_transfer_byte(uint8_t data);
void spi2_write_data(uint8_t *data, int len);
#endif