#include "led.h"
#include "driver/gpio.h"

/*GPIO初始化函数*/
void led_init(void)
{
	esp_err_t err;//定义一个esp_err_t类型的变量err存储返回值

    gpio_config_t gpio_cfg = {//配置结构体
        .intr_type = GPIO_INTR_DISABLE,//不开启中断
        .mode = GPIO_MODE_INPUT_OUTPUT,//输入输出模式
        .pin_bit_mask = (1ull<<GPIO_NUM_38)|(1ull<<GPIO_NUM_39)|(1ull<<GPIO_NUM_41)|(1ull<<GPIO_NUM_42),//使用掩码的方式配置gpio
        .pull_down_en = GPIO_PULLDOWN_DISABLE,//关闭下拉电阻
        .pull_up_en = GPIO_PULLUP_ENABLE,//开启上拉电阻

    };

    /*初始化异常报错*/
    err = gpio_config(&gpio_cfg);
    if(err != ESP_OK)
    {
        printf("gpio init error!\r\n");
    }

    /*配置默认为高电平*/
    gpio_set_level(GPIO_NUM_38,1);
    gpio_set_level(GPIO_NUM_39,1);
    gpio_set_level(GPIO_NUM_41,1);
    gpio_set_level(GPIO_NUM_42,1);
}

/*GPIO翻转函数*/
void gpio_toggle(gpio_num_t gpio_num)
{
	if( gpio_get_level( gpio_num ) == 1 )
	{
		gpio_set_level(gpio_num, 0);
	}
	else
	{
		gpio_set_level(gpio_num, 1);
	}
}