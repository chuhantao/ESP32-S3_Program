#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "lcd.h"

void app_main(void)
{
    lcd_init();//初始化
    lcd_clear(BLACK);//清屏
    lcd_show_char(1,1,'A',YELLOW,BLACK);//显示一个字符
    lcd_show_string(2,1,"HELLOWORLD",GREEN,BLACK);//显示字符串
    lcd_show_num(3,1,12345678,8,RED,BLACK);//显示十进制数字
    lcd_show_hexnum(4,1,0x1234,4,BLUE,BLACK);//显示十六进制数字
    lcd_show_float(5,1,123.45,5,BROWN,BLACK);//显示浮点数
    while (1)
    { 
        vTaskDelay(100);
    }
}