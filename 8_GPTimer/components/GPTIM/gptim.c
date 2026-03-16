#include "gptim.h"
#include "driver/gptimer.h"
#include "esp_attr.h"//在IRAM中运行的函数声明的头文件

/*定义定时器句柄*/
gptimer_handle_t gptimer = NULL;
uint8_t flag_timer = 0 ;//定义标志位变量
bool IRAM_ATTR TimerCallback (gptimer_handle_t timer, const gptimer_alarm_event_data_t *edata, void *user_ctx);//在IRAM中运行的函数声明

/*通用定时器初始化函数*/
void gptimer_init(void)
{
    /*配置时钟源和计数器函数*/
    gptimer_config_t    gptimer_structure = {
        .clk_src = GPTIMER_CLK_SRC_DEFAULT,//选择默认时钟源
        .direction = GPTIMER_COUNT_UP,//计数方向：向上计数
        .flags.intr_shared = 0,//不共享中断函数
        .intr_priority = 0,//自动分配优先级
        .resolution_hz = 1000000,//计数器分辨率：1us
    };
    gptimer_new_timer(&gptimer_structure, &gptimer);

    /*配置比较器动作（报警）函数*/
    gptimer_alarm_config_t  alarm_structure = {
        .alarm_count = 500000,//设置500000次（500ms）
        .flags.auto_reload_on_alarm = 1,//开启自动重装载（循环计数）
        .reload_count  = 0,//设置重装值为0
    };
    gptimer_set_alarm_action(gptimer, &alarm_structure);

    /*配置报警事件函数*/
    gptimer_event_callbacks_t   callbacks_structure = {
        .on_alarm = TimerCallback,
    };
    gptimer_register_event_callbacks(gptimer, &callbacks_structure, NULL);

    /*使能通用定时器*/
    gptimer_enable(gptimer);//定时器句柄

    /*开启通用定时器*/
    gptimer_start(gptimer);//定时器句柄

}

/*中断函数*/
bool IRAM_ATTR TimerCallback (gptimer_handle_t timer, const gptimer_alarm_event_data_t *edata, void *user_ctx)
{
    flag_timer = 1 ;
    return 0 ;
}
