#include "bh1750.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/i2c.h"
#include "iic.h"

/*数据发送函数*/
void bh1750_send_cmd(uint8_t cmd_data)
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();//创建I2C命令链
    i2c_master_start(cmd);//发送I2C起始信号
    i2c_master_write_byte(cmd, bh1750_write_addr, true);//发送BH1750写地址（接收应答）
    i2c_master_write_byte(cmd, cmd_data, true);//发送BH1750命令（接收应答）
    i2c_master_stop(cmd);//发送I2C停止信号
    i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000);//执行I2C命令链（1000ms超时）
    i2c_cmd_link_delete(cmd);//删除I2C命令链，释放内存
}

/*数据接收函数*/
uint16_t bh1750_read_data(void)
{
    uint8_t light_high = 0, light_low = 0;//定义变量存储高字节和低字节数据
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();//创建I2C命令链
    i2c_master_start(cmd);//发送I2C起始信号
    i2c_master_write_byte(cmd, bh1750_read_addr, true);//发送BH1750读地址（接收应答）
    i2c_master_read_byte(cmd, &light_high, I2C_MASTER_ACK);//读取高字节数据（发送应答）
    i2c_master_read_byte(cmd, &light_low, I2C_MASTER_NACK);//读取低字节数据（发送非应答）
    i2c_master_stop(cmd);//发送I2C停止信号
    i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000);//执行I2C命令链（1000ms超时）
    i2c_cmd_link_delete(cmd);//删除I2C命令链，释放内存
    return light_high<<8|light_low;//返回合并后的16位数据
}

/*初始化函数*/
void bh1750_init(void)
{
    iic_init();//初始化I2C
    bh1750_send_cmd(PowerOn);//发送上电命令
    bh1750_send_cmd(HResolutionMode);//发送高分辨率连续工作模式命令
    vTaskDelay(200);//延时200ms等待传感器就绪
}