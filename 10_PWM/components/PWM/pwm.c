#include "pwm.h"
#include "driver/ledc.h"

/*初始化PWM函数*/
void pwm_init(void)
{
    /*配置时钟源和定时器参数函数*/
    ledc_timer_config_t ledctimer_structure = {
        .clk_cfg = LEDC_AUTO_CLK,//自动选择时钟源
        .duty_resolution = LEDC_TIMER_10_BIT,//设置占空比分辨率10位
        .freq_hz = 1000,//频率为1000HZ
        .speed_mode = LEDC_LOW_SPEED_MODE,//输出模式为低速模式
        .timer_num = LEDC_TIMER_1,//选择定时器1
    };
    ledc_timer_config(&ledctimer_structure);

    /*PWM控制器参数配置函数*/
    ledc_channel_config_t   ledcchannel_structure = {
        .channel = LEDC_CHANNEL_1,//使用通道1
        .duty = 512,//占空比设置为512（范围为0-1024，对应0%-100%）
        .flags.output_invert = 0,//输出不反转
        .gpio_num = GPIO_NUM_38,//GPIO38
        .hpoint = 0,//相位偏移为0
        .intr_type = LEDC_INTR_DISABLE,//不使用中断
        .speed_mode = LEDC_LOW_SPEED_MODE,//使用低速模式
        .timer_sel = LEDC_TIMER_1,//选择定时器1
    };
    ledc_channel_config(&ledcchannel_structure);
}

/*修改占空比函数*/
void duty_set(uint16_t duty)
{
    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1, duty);//设置占空比
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1);//更新占空比
}