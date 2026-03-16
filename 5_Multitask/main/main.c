#include <stdio.h>
#include "freertos/FreeRTOS.h"//引入Freertos头文件
#include "freertos/task.h"//引入Freertos头文件
#include "driver/gpio.h"
#include "led.h"
#include "key.h"

void led_task(void* param)
{
     uint8_t key_num = 0 ;
     while(1)
     {
         key_num = key_scan();
          if(key_num == 1)
          {
               gpio_toggle(GPIO_NUM_39);
          } 
          vTaskDelay(5);//必须增加延时
     }
}

void key_task(void *param)
{
     while (1)
     {
          gpio_toggle(GPIO_NUM_38);
          vTaskDelay(100);//必须增加延时
     }
}

void app_main(void)
{
    led_init();
    key_init();

    xTaskCreatePinnedToCore(led_task,"led_task",1024,NULL,1,NULL,0);//函数名称。任务名称，堆栈大小（字节），传入值，任务优先级，任务句柄，分配内核（0/1）
    xTaskCreatePinnedToCore(key_task,"key_task",1024,NULL,1,NULL,0);
}