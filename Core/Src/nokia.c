#include "font.h"
#include "nokia.h"
#include "delay.h"

void LCD_init(void) // 初始化函数
{

    // 产生一个让lcd复位的低电平脉冲
    LCD_RST_0;
    HAL_Delay(1);
    LCD_RST_1;
    // 关闭lcd
    LCD_CE_0;
    HAL_Delay(1);
    // 使能lcd
    LCD_CE_1;
    HAL_Delay(1);
    LCD_write_byte(0x21, 0);
    LCD_write_byte(0xc8, 0);
    LCD_write_byte(0x06, 0);
    LCD_write_byte(0x13, 0);
    LCD_write_byte(0x20, 0);
    LCD_clear();
    LCD_write_byte(0x0c, 0);
    // 关闭lcd
    LCD_CE_0;
}

void LCD_clear(void) // 清屏函数
{
    unsigned int i;

    LCD_write_byte(0x0c, 0);
    LCD_write_byte(0x80, 0);

    for (i = 0; i < 504; i++)
        LCD_write_byte(0, 1);
}

void LCD_set_XY(unsigned char X, unsigned char Y) // 光标移动函数
{
    LCD_write_byte(0x40 | Y, 0); // column
    LCD_write_byte(0x80 | X, 0); // row
}

void LCD_write_char(unsigned char c) // 在目前光标位置写单个字符函数
{
    unsigned char line;
    c -= 32;
    for (line = 0; line < 6; line++)
        LCD_write_byte(font6x8[c][line], 1);
}

void LCD_write_number(unsigned char X, unsigned char Y, unsigned int num) // 写99以内数字函数
{
    // 如果数字大于99
    if (num > 99)
        LCD_write_english_string(X, Y, "ERROR!");
    else
    {
        unsigned char a, b; // a,b,c,d,e分别代表数字的万千百十个位
        a = num / 10;
        b = num % 10;
        a += 48;
        b += 48;
        LCD_set_XY(X, Y);
        LCD_write_char(a);
        X++;
        LCD_write_char(b);
        X++;
    }
}

void LCD_write_english_string(unsigned char X, unsigned char Y, char *s) // 写英文字符串函数
{

    LCD_set_XY(X, Y);
    while (*s)
    {
        LCD_write_char(*s);
        s++;
    }
}

void LCD_write_byte(unsigned char dat, unsigned char command) // 写入指令函数
{
    unsigned char i;
    LCD_CE_0;
    if (command == 0)
        LCD_DC_0;
    else
        LCD_DC_1;
    for (i = 0; i < 8; i++)
    {
        if (dat & 0x80)
            SDIN_1;
        else
            SDIN_0;
        SCLK_0;
        delay_us(10);
        dat = dat << 1;
        SCLK_1;
    }
    LCD_CE_1;
}
