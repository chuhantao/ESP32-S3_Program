#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "myuart.h"

void app_main(void)
{
    int length = 0 ;
    uint8_t receive_data[1024] = {0};//定义数组，用于存储读取到的数据
    uart_init();
    while (1)
    {
        length = uart_read_bytes(UART_NUM_1, receive_data, 1024, 100);//从UART1读取数据，最多1024字节，等待100ms
        if(length > 0 )
        {
            uart_write_bytes(UART_NUM_1, receive_data, length);//将读取到的数据写入UART1
            uart_flush(UART_NUM_1);//刷新UART1发送缓冲区
        }
        vTaskDelay(5);
    }
}