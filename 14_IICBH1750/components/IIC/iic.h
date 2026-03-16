#ifndef __IIC_H_
#define __IIC_H_

/*I2C引脚定义宏*/
#define I2C_SCL_PIN GPIO_NUM_4    // SCL引脚
#define I2C_SDA_PIN GPIO_NUM_5    // SDA引脚

void iic_init(void);

#endif