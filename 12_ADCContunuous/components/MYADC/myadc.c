#include "myadc.h"
#include "hal/adc_types.h"
#include "esp_adc/adc_continuous.h"

uint8_t *data_value;//存储转换帧的地址
uint16_t adc_value_rl;//存储通道3的转换结果
//uint8_t adc_channelnum_rp;
uint16_t adc_value_rp;//存储通道4的转换结果
//uint8_t adc_channelnum_rl;
//uint8_t flag_adc_conv = 0 ;

adc_continuous_handle_t adc_countinuous_handle ;//ADC连续转换句柄

/* 转换完成后产生回调函数 */
bool continuous_callback(adc_continuous_handle_t handle, const adc_continuous_evt_data_t *edata, void *user_data)
{
    data_value = edata->conv_frame_buffer;//获取转换帧的地址
    if(edata->size == 8)//判断转换帧的大小是否为8字节
    {
        adc_value_rl = ((data_value[1] & 0x0F) << 8) | data_value[0];//获取高字节的低4位，将这4位移到高8位位置，与低字节组合，形成完整的12位ADC值
        //adc_channelnum_rp = data_value[1] >> 5 ;
        adc_value_rp = ((data_value[5] & 0x0F) << 8) | data_value[4];//获取高字节的低4位，将这4位移到高8位位置，与低字节组合，形成完整的12位ADC值
        //adc_channelnum_rl = data_value[5] >> 5 ;
        return true;
    }
    return false ;
}

/*初始化ADC函数*/
void adc_init(void)
{
    /*配置转换结果存储单元大小和转换帧存储单元大小*/
    adc_continuous_handle_cfg_t adc_contunuous_structure = {
        .conv_frame_size = 8,//每个转换帧的大小，单位为字节（一个转换结果占用4字节）
        .max_store_buf_size = 1024,//最大转换结果存储单元大小，单位为字节
    };
    adc_continuous_new_handle(&adc_contunuous_structure, &adc_countinuous_handle);

    /*配置ADC转换表（结构体数组）*/
    adc_digi_pattern_config_t adc_digi_arr[] = {
        {
            .atten = ADC_ATTEN_DB_11,       // 11dB衰减
            .bit_width = ADC_BITWIDTH_12,   // 输出12bit
            .channel = ADC_CHANNEL_3,       // 通道3（与IO4对应）
            .unit = ADC_UNIT_1              // ADC1
        },
        {
            .atten = ADC_ATTEN_DB_11,       // 11dB衰减
            .bit_width = ADC_BITWIDTH_12,   // 输出12bit
            .channel = ADC_CHANNEL_4,       // 通道4（与IO5对应）
            .unit = ADC_UNIT_1              // ADC1
        }
    };

    /*配置ADC总控制器需要下发和执行的参数*/
    adc_continuous_config_t continuous_config_structure = {
        .adc_pattern = adc_digi_arr,//ADC转换表（结构体数组）
        .conv_mode = ADC_CONV_SINGLE_UNIT_1,//ADC转换模式（单通道，ADC1）
        .format = ADC_DIGI_OUTPUT_FORMAT_TYPE2,//ADC转换结果格式（类型2）
        .pattern_num = 2,//ADC转换表（结构体数组）中元素的数量（2个通道）
        .sample_freq_hz = 20000,//采样频率（20000Hz）
    };
    adc_continuous_config(adc_countinuous_handle, &continuous_config_structure);

    /*注册回调函数，用于数据读取*/
    adc_continuous_evt_cbs_t evt_stucture = {
        .on_conv_done = continuous_callback,//转换完成后产生回调函数
    };
    adc_continuous_register_event_callbacks(adc_countinuous_handle, &evt_stucture, NULL);

    /*启动ADC连续转换*/
    adc_continuous_start(adc_countinuous_handle);            
}