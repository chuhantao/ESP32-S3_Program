#include "key.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

/*GPIO初始化函数*/
void key_init(void)
{
    gpio_config_t gpio_structure = {
        .intr_type = GPIO_INTR_DISABLE,//不开启中断
        .mode = GPIO_MODE_INPUT,//输入模式
        .pin_bit_mask = (1ull<<GPIO_NUM_9),//使用掩码的方式配置gpio9，10，11，12
        .pull_down_en = GPIO_PULLDOWN_DISABLE,//关闭下拉电阻
        .pull_up_en = GPIO_PULLUP_ENABLE,//开启上拉电阻
    };
    gpio_config(&gpio_structure);
}

/*按键扫描函数*/
uint8_t key_scan(void)
{
    uint8_t key_num = 0 ;//定义变量，存储按键按下的编号
    if(gpio_get_level(GPIO_NUM_9) == 0)//检测按键是否按下
    {
        vTaskDelay(20);//消抖
        while(gpio_get_level(GPIO_NUM_9) == 0); //循环至松手
        vTaskDelay(20);//消抖
        key_num = 1;
    }
    return key_num;//返回按键按下的编号
}