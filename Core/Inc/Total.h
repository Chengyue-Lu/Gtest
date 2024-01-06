#ifndef TOTAL_H__
#define TOTAL_H__

enum task_state
{
    wait,  // 等待指令
    music, // 播放音乐
    play,  // 弹奏模式
    other, // 其他模式
};

typedef struct
{
    char music_name[20];
    int *musickey;
    int length;
    int chnum;
} Musicstorage; // 单独曲目存储函数

typedef struct
{
    int keyhigh; // 目前对应的音高
    int volume;  // 响度
    int time;    // 时间
} Keyplay;

typedef struct
{
    int key_p; // 按下按键
} Keyboard;    // 按键模块

typedef struct
{
    int key;      // 此时音高
    char output;  // 输出口
    int progress; // 播放进度
} Channel_play;   // 频道播放

typedef struct
{
    Channel_play lowchannel;
    Channel_play highchannel;
    Channel_play voicechannel;
    int num_music;
    int volume;
    int speed;
    int flag;
    enum State
    {
        stop,
        sing,
    } state;
} Play; // 总播放模块，包括音量，速度，曲目数，不同的声道

typedef struct
{
    Musicstorage music1;
    Musicstorage music2;
    Musicstorage music3;
} Musicall; // 音乐存储结构体

typedef struct
{
    Play play;
    Keyplay keyplay;
    Keyboard keyboard;
    enum task_state task;
    Musicall musicall;
} Total; // 整体

#endif