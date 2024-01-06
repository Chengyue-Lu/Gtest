#include "lcd.h"
extern char buffer[8];
extern Total total;
void lcd_display() // 根据不同场景进行LCD显示内容更新函数
{
    LCD_clear();
    switch (total.task)
    {
    case wait: // 等待按键提示press1
        LCD_write_english_string(0, 2, welcome1);
        break;
    case music: // 显示目前播放曲目数，名称，速度，音量
        if (total.play.num_music == 1)
            LCD_write_english_string(0, 0, &total.musicall.music1.music_name);
        if (total.play.num_music == 2)
            LCD_write_english_string(0, 0, &total.musicall.music2.music_name);
        if (total.play.num_music == 3)
            LCD_write_english_string(0, 0, &total.musicall.music3.music_name);

        LCD_write_english_string(0, 1, mu3);
        LCD_write_number(60, 1, total.play.num_music);
        LCD_write_english_string(0, 2, mu1);
        LCD_write_number(60, 2, total.play.volume);
        LCD_write_english_string(0, 3, mu2);
        LCD_write_number(60, 3, total.play.speed);
        break;
    case play: // 显示目前弹奏音高，音量以及弹奏时间
        LCD_write_english_string(0, 1, key3);
        LCD_write_number(60, 1, total.keyplay.keyhigh);
        LCD_write_english_string(0, 2, key1);
        LCD_write_number(60, 2, total.keyplay.volume);
        LCD_write_english_string(0, 3, key2);
        LCD_write_number(60, 3, total.keyplay.time);
        break;
    default:
        break;
    }
}