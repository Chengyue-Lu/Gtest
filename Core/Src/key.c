#include "key.h"
#include "main.h"
extern Total total;
extern int temp;
extern int flag_key;
void key_init(Keyboard *keyboard) // 键盘结构体初始化函数
{
    keyboard->key_p = 0;
}
void key_deal(Keyboard *keyboard) // 针对不同场景下收到的键盘信息进行不同响应
{
    switch (total.task)
    {
    case wait:
        if (keyboard->key_p == 1)
            total.task = music;
        break;
    case music:
        if (keyboard->key_p == 1)
        {
            total.task = play;
            music_init(&total.play);
        }
        if (keyboard->key_p == 2)
        {
            if (total.play.state == sing)
            {
                temp = total.play.num_music;
                music_start(&total.play, 0);
            }
            if (total.play.state == stop)
            {
                music_start(&total.play, temp);
            }
        }
        if (keyboard->key_p == 3)
        {
            temp = total.play.num_music + 1;
            if (temp > 3)
                temp = 1;
            music_start(&total.play, temp);
        }
        if (keyboard->key_p == 4)
        {
            temp = total.play.num_music - 1;
            if (temp < 1)
                temp = 3;
            music_start(&total.play, temp);
        }
        if (keyboard->key_p == 5)
            total.play.volume++;
        if (keyboard->key_p == 6)
            total.play.volume--;
        if (keyboard->key_p == 7)
            total.play.speed++;
        if (keyboard->key_p == 8)
            total.play.speed--;
        break;
    case play:
        if (keyboard->key_p == 1)
            total.task = music;
        if (keyboard->key_p == 3)
            total.keyplay.keyhigh++;
        if (keyboard->key_p == 4)
            total.keyplay.keyhigh--;
        if (keyboard->key_p == 2)
            flag_key = total.keyplay.time;
        if (keyboard->key_p == 5)
            total.keyplay.volume++;
        if (keyboard->key_p == 6)
            total.keyplay.volume--;
        if (keyboard->key_p == 7)
            total.keyplay.time++;
        if (keyboard->key_p == 8)
            total.keyplay.time--;

        if (total.keyplay.keyhigh > 21)
            total.keyplay.keyhigh = 1;
        if (total.keyplay.keyhigh < 1)
            total.keyplay.keyhigh = 21;
        break;
    default:
        break;
    }
    keyboard->key_p = 0;
};