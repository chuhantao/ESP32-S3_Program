#ifndef __LED_H_
#define __LED_H_

#include "driver/gpio.h"//调用gpio头文件

void led_init(void);
void gpio_toggle(gpio_num_t gpio_num);

#endif
