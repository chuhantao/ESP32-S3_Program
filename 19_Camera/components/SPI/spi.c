#include "spi.h"
#include <string.h>
#include "driver/spi_master.h"
#include "driver/gpio.h"

spi_device_handle_t spi2_handle;//SPI2从设备句柄

/*初始化SPI函数*/
void spi2_init(void)
{
    /*配置SPI控制器参数和GPIO交换矩阵*/
    spi_bus_config_t  spibus_structure = {
        .flags = SPICOMMON_BUSFLAG_MASTER,//自动检测SPI
        .intr_flags = 0,//不使用中断
        .isr_cpu_id = INTR_CPU_ID_AUTO,//自动选择中断CPU
        .max_transfer_sz = 240 * 240 * 2,//最大传输大小
        .miso_io_num = SPI2_MISO_PIN,//MISO引脚
        .mosi_io_num = SPI2_MOSI_PIN,//MOSI引脚
        .sclk_io_num = SPI2_SCLK_PIN,//SCLK引脚
        .quadhd_io_num = -1,//不使用
        .quadwp_io_num = -1,//不使用
    };
    spi_bus_initialize(SPI2_HOST,& spibus_structure, SPI_DMA_CH_AUTO);//SPI2，指针，DMA通道自动选择

    /*向SPI总线添加从设备信息*/
    spi_device_interface_config_t spidevice_structure = {
        .clock_source = SPI_CLK_SRC_DEFAULT,//默认时钟源
        .clock_speed_hz = 60000000,//通信速度60MHz
        .mode = 0,//通信模式0
        .queue_size = 7,//传输队列大小7
        .spics_io_num = SPI2_CS_PIN,//CS引脚
    };
    spi_bus_add_device(SPI2_HOST, &spidevice_structure, &spi2_handle);//SPI2，指针，从设备句柄
}

/*数据交换函数*/
uint8_t spi2_transfer_byte(uint8_t data)
{
    spi_transaction_t t = {0};//定义结构体并初始化为0
    //memset(&t, 0, sizeof(t));
    //t.flags = SPI_TRANS_USE_TXDATA | SPI_TRANS_USE_RXDATA;
    t.length = 8;//传输8位数据
    t.tx_data[0] = data;//发送数据
    spi_device_polling_transmit(spi2_handle, &t);//SPI句柄，指针
    return t.rx_data[0];//返回接收数据
}

/*数据发送函数*/
void spi2_write_data(uint8_t *data, int len)
{
    spi_transaction_t t = {0};//定义结构体并初始化为0
    t.length = len * 8;//传输数据长度为len个字节，每个字节8位
    t.tx_buffer = data;//发送数据指针
    spi_device_polling_transmit(spi2_handle, &t);//SPI句柄，指针
}