#ifndef __BH1750_H_
#define __BH1750_H_

#include <stdint.h>

/*BH1750地址定义*/
#define bh1750_write_addr 0x46 //BH1750写地址 (7位设备地址0x23 << 1)
#define bh1750_read_addr  0x47 //BH1750读地址 (7位设备地址0x23 << 1 | 0x01)

/*BH1750命令定义*/
#define PowerDown               0x00 // 掉电模式，最低功耗
#define PowerOn                 0x01 // 上电模式，等待测量指令
#define Reset                   0x07 // 重置数据寄存器值
#define HResolutionMode         0x10 // 高分辨率模式，1lx精度，测量时间120ms
#define HResolutionMode2        0x11 // 高分辨率模式2，0.5lx精度，测量时间120ms
#define LResolutionMode         0x13 // 低分辨率模式，4lx精度，测量时间16ms
#define OneTimeHResolutionMode  0x20 // 单次高分辨率模式，1lx精度，测量时间120ms，测量后自动断电
#define OneTimeHResolutionMode2 0x21 // 单次高分辨率模式2，0.5lx精度，测量时间120ms，测量后自动断电
#define OneTimeLResolutionMode  0x23 // 单次低分辨率模式，4lx精度，测量时间16ms，测量后自动断电

void bh1750_send_cmd(uint8_t cmd_data);
uint16_t bh1750_read_data(void);
void bh1750_init(void);

#endif