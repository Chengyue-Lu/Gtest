#include "music.h"
#include "Total.h"
#include "lcd.h"
#include "storagemusic.h"
#include "stm32g4xx_hal.h"

extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim15;
extern TIM_HandleTypeDef htim16;
extern TIM_HandleTypeDef htim17;
extern int flag_key;

void music_init(Play *play) // 音乐演奏结构体初始化
{
    play->highchannel.key = 0;
    play->highchannel.output = 1;
    play->highchannel.progress = 0;
    play->lowchannel.key = 0;
    play->lowchannel.output = 2;
    play->lowchannel.progress = 0;
    play->voicechannel.key = 0;
    play->voicechannel.output = 3;
    play->voicechannel.progress = 0;
    play->num_music = 0;
    play->volume = 5;
    play->speed = 1;
    play->flag = 0;
    play->state = stop;
};
void mustorage_init(Musicall *musicall) // 音乐按键姓名，通道等信息存储初始化
{
    musicall->music1.chnum = 1;
    musicall->music1.length = 266;
    for (int i = 0; i < 20; i++)
    {
        musicall->music1.music_name[i] = name1[i];
    }
    musicall->music1.musickey = music1k;
    musicall->music2.chnum = 2;
    musicall->music2.length = 192;
    for (int i = 0; i < 20; i++)
    {
        musicall->music2.music_name[i] = name2[i];
    }
    musicall->music2.musickey = music2k;
    musicall->music3.chnum = 1;
    musicall->music3.length = 122;
    for (int i = 0; i < 20; i++)
    {
        musicall->music3.music_name[i] = name3[i];
    }
    musicall->music3.musickey = music3k;
}
void singing(Play *play) // 演奏过程函数，用于定时给函数弹奏进度增加
{
    if (play->num_music != 0)
    {
        if (play->flag <= play->speed)
            play->flag++;
        else
        {
            play->highchannel.progress++;
            play->lowchannel.progress++;
            play->voicechannel.progress++;
            play->flag = 0;
        }
    }
}

void music_play(Play *play, Musicall *musicall) // 音乐演奏函数，用于将乐谱信息传导给channel
{
    if (play->num_music != 0)
        play->state = sing;
    else
        play->state = stop;
    if (play->num_music == 1)
    {
        play->voicechannel.key = musicall->music1.musickey[play->voicechannel.progress];
        pwm_move(3, play);
    }
    if (play->num_music == 2)
    {
        play->voicechannel.key = musicall->music2.musickey[play->voicechannel.progress];
        pwm_move(3, play);
        play->highchannel.key = musicall->music2.musickey[play->highchannel.progress + musicall->music2.length - 1];
        pwm_move(1, play);
    }
    if (play->num_music == 3)
    {
        play->highchannel.key = musicall->music3.musickey[play->highchannel.progress];
        pwm_move(1, play);
    }
};

void music_start(Play *play, int num) // 音乐开始函数，用于启动音乐播放
{
    play->highchannel.key = 0;
    play->highchannel.progress = 0;
    play->lowchannel.key = 0;
    play->lowchannel.progress = 0;
    play->voicechannel.key = 0;
    play->voicechannel.progress = 0;
    play->flag = 0;
    play->num_music = num;
    pwm_init(play);
};

void music_stop(Play *play, Musicall *musicall) // 音乐停止函数，当音乐播放结束后自动停止并归位
{
    if (play->num_music == 1)
    {
        if (play->voicechannel.progress >= musicall->music1.length)
        {
            play->num_music = 0;
            music_start(play, 0);
            lcd_display();
            pwm_init(play);
        }
    }
    if (play->num_music == 2)
    {
        if (play->highchannel.progress >= musicall->music2.length)
        {
            play->num_music = 0;
            music_start(play, 0);
            lcd_display();
            pwm_init(play);
        }
    }
    if (play->num_music == 3)
    {
        if (play->highchannel.progress >= musicall->music3.length)
        {
            play->num_music = 0;
            music_start(play, 0);
            lcd_display();
            pwm_init(play);
        }
    }
}

void pwm_init(Play *play) // PWM初始化函数
{
    if (play->num_music == 0)
    {
        HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
        HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_1);
        HAL_TIM_PWM_Stop(&htim17, TIM_CHANNEL_1);
    }
    if (play->num_music == 1)
    {
        HAL_TIM_PWM_Start(&htim17, TIM_CHANNEL_1);
        HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_1);
        HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
    }
    if (play->num_music == 2)
    {
        HAL_TIM_PWM_Start(&htim17, TIM_CHANNEL_1);
        HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
        HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_1);
    }
    if (play->num_music == 3)
    {
        HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
        HAL_TIM_PWM_Stop(&htim17, TIM_CHANNEL_1);
        HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_1);
    }
}
void pwm_move(int outch, Play *play) // PWMccrarr信息更新函数
{
    switch (outch)
    {
    case 1:
        TIM3->ARR = 1000000 / b_freq[play->highchannel.key];
        TIM3->CCR1 = TIM3->ARR * play->volume / 10;
        break;
    case 2:
        TIM2->ARR = 1000000 / b_freq[play->lowchannel.key];
        TIM2->CCR1 = TIM2->ARR * play->volume / 10;
        break;
    case 3:
        TIM17->ARR = 1000000 / b_freq[play->voicechannel.key];
        TIM17->CCR1 = TIM17->ARR * play->volume / 10;
        break;
    default:
        break;
    }
};

void keyplay_init(Keyplay *keyplay) // 按键弹奏信息初始化函数
{
    keyplay->keyhigh = 0;
    keyplay->time = 10;
    keyplay->volume = 5;
}

void key_play(Keyplay *keyplay) // 播放目前弹奏内容函数
{
    if (flag_key > 0)
    {
        HAL_TIM_PWM_Start(&htim17, TIM_CHANNEL_1);
        TIM17->ARR = 1000000 / b_freq[keyplay->keyhigh];
        TIM17->CCR1 = TIM17->ARR * keyplay->volume / 10;
    }
    else if (total.task == play)
        HAL_TIM_PWM_Stop(&htim17, TIM_CHANNEL_1);
}