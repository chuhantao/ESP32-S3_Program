#include "myadc.h"
#include "driver/adc.h"
#include "esp_adc/adc_oneshot.h"

adc_oneshot_unit_handle_t adc_unit_handle ;//定义ADC1句柄

void adc_init(void)
{
    /*配置时钟源，ADC参数*/
    adc_oneshot_unit_init_cfg_t oneshot_structure = {
        .clk_src = ADC_RTC_CLK_SRC_DEFAULT,//默认时钟源
        .ulp_mode = ADC_ULP_MODE_DISABLE,//不使用低功耗协处理器
        .unit_id = ADC_UNIT_1,//ADC1
    };
    adc_oneshot_new_unit(&oneshot_structure, &adc_unit_handle);

    /*配置总控制器下发和执行的参数*/
    adc_oneshot_chan_cfg_t oneshot_chan_structure = {
        .atten = ADC_ATTEN_DB_11,//电压衰减系数：11dB衰减
        .bitwidth = ADC_BITWIDTH_12,//12位分辨率
    };
    adc_oneshot_config_channel(adc_unit_handle, ADC_CHANNEL_3, &oneshot_chan_structure);
    adc_oneshot_config_channel(adc_unit_handle, ADC_CHANNEL_4, &oneshot_chan_structure);
}