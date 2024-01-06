#ifndef INC_DELAY_H_
#define INC_DELAY_H_
#include "main.h"

void delay_us(unsigned long udelay) // us级delay函数
{
    __IO unsigned long Delay = udelay * 100; //(SystemCoreClock / 8U / 1000000U)
    do
    {
        __NOP();
    } while (Delay--);
}

#endif