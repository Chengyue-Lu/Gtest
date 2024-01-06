#include "Init.h"
extern int rxkey;
extern Total total;
void Total_Init(Total *total) // 全局结构体初始化
{
    music_init(&total->play);
    key_init(&total->keyboard);
    mustorage_init(&total->musicall);
    keyplay_init(&total->keyplay);
    total->task = wait;
};