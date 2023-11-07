#pragma once
#include "internal.h"

namespace GameEngine
{

    enum Channels
    {
        CH_ALL = -1,
        CH_INTRO = 1,
        CH_LOOP,
        CH_FX,
    };

    void playMusicSet(Mix_Chunk* intro, Mix_Chunk* loop, int fade = 5000);
    void playSoundEffect(Mix_Chunk* chunk);

    void haltMusic();

    void fadeOutMusic(int fade = 5000);

    bool getMuteState();
    void setMuteState(bool _mute);

    //int getMusicVolume();
    //int getSoundEffectVolume();
    //
    //void setMusicVolume();
    //void setSoundEffectVolume();

}