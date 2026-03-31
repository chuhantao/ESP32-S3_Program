#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

void app_main(void)
{
    while (1)
    {
        printf("This is printf!\r\n");//普通串口打印
        ESP_LOGI("main","This is an information!\r\n");//打印信息
        ESP_LOGE("main","This is an error!\r\n");//打印报错
        vTaskDelay(500);//延时函数
    }
}