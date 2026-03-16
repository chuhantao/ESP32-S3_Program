#include "iic.h"
#include "driver/gpio.h"
#include "driver/i2c.h"

/*I2C初始化函数*/
void iic_init(void)
{
    /*配置时钟源，引脚，I2C参数*/
    i2c_config_t i2c_structure = {
        .clk_flags = 0,//自动选择时钟源
        .master.clk_speed = 100000,//I2C时钟速度100kHz
        .mode = I2C_MODE_MASTER,//I2C模式为主机
        .scl_io_num = I2C_SCL_PIN,//SCL引脚
        .scl_pullup_en = GPIO_PULLUP_ENABLE,//SCL引脚开启上拉
        .sda_io_num = I2C_SDA_PIN,//SDA引脚
        .sda_pullup_en = GPIO_PULLUP_ENABLE,//SDA引脚开启上拉
    };
    i2c_param_config(I2C_NUM_0, &i2c_structure);//使用的I2C通道，I2C参数结构体指针

    /*注册I2C*/
    i2c_driver_install(I2C_NUM_0, I2C_MODE_MASTER, 0, 0, 0);//使用的I2C通道，I2C主机模式，接收缓冲区大小（从机），发送缓冲区大小（从机），I2C中断标志（0：不使用中断）
}