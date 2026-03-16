#include <stdio.h>
#include "freertos/FreeRTOS.h"//引入Freertos头文件
#include "freertos/task.h"//引入Freertos头文件
#include "driver/gpio.h"
#include "led.h"

void app_main(void)
{
    led_init();
    
    while (1)
    {
        gpio_toggle(GPIO_NUM_38);//38引脚翻转电平
        vTaskDelay(500);//延时500ms
    }
}