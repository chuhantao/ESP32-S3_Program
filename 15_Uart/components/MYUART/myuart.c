#include "myuart.h"
#include "driver/uart.h"
#include "driver/gpio.h"

/*UART初始化函数*/
void uart_init(void)
{
    /*配置核心控制器参数函数*/
    uart_config_t uart_structure = {
        .baud_rate = 9600,//波特率
        .data_bits = UART_DATA_8_BITS,//数据位长度
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,//不使用硬件流控制
        .parity = UART_PARITY_DISABLE,//不使用校验位
        .rx_flow_ctrl_thresh = 100,//接收流控制阈值（不开启无所谓）
        .source_clk = UART_SCLK_DEFAULT,//默认时钟源
        .stop_bits = UART_STOP_BITS_1,//1个停止位
    };
    uart_param_config(UART_NUM_1, &uart_structure);//使用UART1

    /*配置UART1引脚函数*/
    uart_set_pin(UART_NUM_1, GPIO_NUM_17, GPIO_NUM_18, -1, -1);//UART1_TXD->GPIO17,UART1_RXD->GPIO18，不使用硬件流控（-1）

    /*配置发送&接收缓冲区函数*/
    uart_driver_install(UART_NUM_1, 1024, 1024, 0, NULL,0);//UART1，1024字节发送&接收缓冲区
}