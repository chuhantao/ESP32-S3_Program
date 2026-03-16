#include "exti.h"
#include "driver/gpio.h"
#include "led.h"

void exti_isr_handler(void *param)//中断服务函数
{
    gpio_toggle(GPIO_NUM_38);
}

/*EXTI初始化函数*/
void exti_init(void)
{
    gpio_config_t gpio_structure = {
        .intr_type = GPIO_INTR_NEGEDGE,//中断下降沿触发
        .mode = GPIO_MODE_INPUT,//输入模式
        .pin_bit_mask = 1ull << GPIO_NUM_9,//IO9
        .pull_down_en = GPIO_PULLDOWN_DISABLE,//不开启下拉
        .pull_up_en = GPIO_PULLUP_ENABLE,//开启上拉
    } ;
    gpio_config(&gpio_structure);

    /*注册中断函数*/
    gpio_install_isr_service(ESP_INTR_FLAG_EDGE);//边沿触发中断

    /*将IO与中断服务函数匹配函数*/
    gpio_isr_handler_add(GPIO_NUM_9,exti_isr_handler,NULL);

    /*开启中断函数*/
    gpio_intr_enable(GPIO_NUM_9);
}

