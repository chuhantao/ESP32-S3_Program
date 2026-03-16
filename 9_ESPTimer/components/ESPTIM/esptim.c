#include "esptim.h"
#include "driver/gpio.h"
#include "esp_timer.h"
#include "led.h"
#include "lcd.h"

uint16_t timer_cnt = 0 ;

void esptimer_callback(void *param)
{
    timer_cnt++;
    lcd_show_num(1,5,timer_cnt,4,YELLOW,BLACK);
    gpio_toggle(GPIO_NUM_38);
}

void esptimer_init(void)
{
    /*定义定时器句柄函数*/
    esp_timer_handle_t esptimer = NULL;

    /*配置定时器参数函数*/
    esp_timer_create_args_t esptimer_structure = {
        .callback = &esptimer_callback,//中断函数配置
        .arg = NULL,//不传入参数
        .dispatch_method = ESP_TIMER_TASK,//不在IRAM中执行
        .skip_unhandled_events = true ,//不处理未处理事件
    };
    esp_timer_create(&esptimer_structure,&esptimer);

    /*配置比较器值函数*/
    esp_timer_start_periodic(esptimer, 500000);//步长固定1us，设置500ms      
}

