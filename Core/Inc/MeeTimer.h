#ifndef _MEETIMER_H_
#define _MEETIMER_H_
typedef unsigned int u16;
typedef unsigned long u32;
#define TRUE 1
#define FALSE 0
// 计时timer结构体初始化
typedef struct
{
    u16 bTag1ms : 1;
    u16 bTag10ms : 1;
    u16 bTag100ms : 1;
    u16 bTag1s : 1;

} STRN_SYS_TIMER;

extern volatile STRN_SYS_TIMER strSysTimer;
extern volatile u32 lSystemCnt;

#endif /* _MEETIMER_H_ */