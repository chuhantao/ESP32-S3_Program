#include "motor.h"
#include "pwm.h"
/*
    角度    占空比
     0      0.025
     45     0.05
     90     0.75
     145    0.1
     180    0.125
占空比 = (角度 * 1/1800 +0.025) * 1024
*/
/*舵机角度计算函数*/
void set_angle(uint8_t angle)
{
    if( angle > 180 )//上限180度
    {
        angle = 180 ;
    }
    uint16_t duty = ((float)angle / 1800 + 0.025 ) * 1024 ;
    duty_set( duty );
}