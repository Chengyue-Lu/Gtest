#ifndef MUSIC_H__
#define MUSIC_H__

#include "Total.h"

extern Total total;
void music_init(Play *play);
void mustorage_init(Musicall *musicall);
void singing(Play *play);
void music_play(Play *play, Musicall *musicall);
void music_start(Play *play, int num);
void music_stop(Play *play, Musicall *musicall);

void pwm_init(Play *play);
void pwm_move(int outch, Play *play);

void keyplay_init(Keyplay *keyplay);
void key_play(Keyplay *keyplay);

static const int b_freq[] = {
    // 对应的频率信息
    1,
    262,  // do 1
    294,  // re 2
    330,  // mi 3
    349,  // fa 4
    392,  // so 5
    440,  // la 6
    494,  // si 7
    523,  // do 1.
    587,  // re 2.
    659,  // mi 3.
    698,  // fa 4.
    784,  // so 5.
    880,  // la 6.
    988,  // si 7.
    1046, // do 1..
    1175, // re 2..
    1318, // mi 3..
    1397, // fa 4..
    1568, // so 5..
    1760, // la 6..
    1976, // si 7..
};

#endif