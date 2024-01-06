#include "loop.h"
#include "MeeTimer.h"
#include "music.h"
#include "Total.h"
#include "key.h"
#include "lcd.h"
extern Total total;
extern int flag_key;
void loop() // 主循环函数，用于计时以及函数的分模块运行
{
    if (strSysTimer.bTag1ms == TRUE)
    {
        /*musicpart begin*/
        /*musicpart end*/
        strSysTimer.bTag1ms = FALSE;
    }
    if (strSysTimer.bTag10ms == TRUE)
    {

        strSysTimer.bTag10ms = FALSE;
    }
    if (strSysTimer.bTag100ms == TRUE)
    {
        /*musicpart begin*/
        singing(&total.play);
        music_play(&total.play, &total.musicall);
        music_stop(&total.play, &total.musicall);
        /*musicpart end*/
        if (flag_key > 0)
            flag_key--;
        key_play(&total.keyplay);
        strSysTimer.bTag100ms = FALSE;
    }
};