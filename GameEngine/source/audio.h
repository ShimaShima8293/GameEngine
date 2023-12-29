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

    void PlayMusicSet(Mix_Chunk* intro, Mix_Chunk* loop, int fade = 5000);
    void PlaySoundEffect(Mix_Chunk* chunk);

    void HaltMusic();

    void FadeOutMusic(int fade = 5000);

    bool GetMuteState();
    void SetMuteState(bool _mute);
}