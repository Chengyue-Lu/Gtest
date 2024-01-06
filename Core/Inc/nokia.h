#ifndef NOKIA_H__
#define NOKIA_H__

// 管脚定义
// 按键操作宏定义
#define SCLK_0 HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, RESET)
#define SCLK_1 HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, SET)
#define SDIN_0 HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, RESET)
#define SDIN_1 HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, SET)
#define LCD_DC_0 HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, RESET)
#define LCD_DC_1 HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, SET)
#define LCD_CE_0 HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, RESET)
#define LCD_CE_1 HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, SET)
#define LCD_RST_0 HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, RESET)
#define LCD_RST_1 HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, SET)

void LCD_init(void);
void LCD_clear(void);
void LCD_set_XY(unsigned char X, unsigned char Y);
void LCD_write_char(unsigned char c);
void LCD_write_number(unsigned char X, unsigned char Y, unsigned int num);
void LCD_write_english_string(unsigned char X, unsigned char Y, char *s);

void LCD_write_byte(unsigned char dat, unsigned char command);

#endif