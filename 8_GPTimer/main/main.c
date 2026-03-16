#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "led.h"
#include "gptim.h"
#include "lcd.h"

uint8_t timer_cnt = 0 ;

void app_main(void)
{
    lcd_init();
    led_init();
    gptimer_init();
    lcd_show_string(1,1,"CNT:",GREEN,BLACK);
    while (1)
    {
        if(flag_timer == 1)//检测到标志位为1时
        {
            timer_cnt++;//显示值+1
            lcd_show_num(1,5,timer_cnt,3,YELLOW,BLACK);//显示字符
            gpio_toggle(GPIO_NUM_38);//翻转电平
            flag_timer = 0 ;//标志位置0
        }
        vTaskDelay(1);//用于freertos底层调度
    }
}