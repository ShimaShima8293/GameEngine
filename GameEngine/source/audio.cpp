#include "audio.h"
#include "vars.h"

namespace GameEngine
{
    bool mute = false;
}

using namespace GameEngine;


void playMusicSet(MusicSet& set)
{
    playMusicSet(set.intro, set.loop, set.fade);
}

void playMusicSet(Mix_Chunk* intro, Mix_Chunk* loop, int fade)
{
    haltMusic();
    Mix_PlayChannel(CH_INTRO, intro, 0);
    Mix_FadeOutChannel(CH_INTRO, fade);

    Mix_FadeInChannel(CH_LOOP, loop, -1, fade);
}

void playSoundEffect(Mix_Chunk* chunk)
{
    Mix_PlayChannel(CH_FX, chunk, 0);
}

void haltMusic()
{
    Mix_HaltChannel(CH_INTRO);
    Mix_HaltChannel(CH_LOOP);
}

void fadeOutMusic(int fade)
{
    Mix_FadeOutChannel(CH_INTRO, fade);
    Mix_FadeOutChannel(CH_LOOP, fade);
}

bool getMuteState()
{
    return mute;
}

void setMuteState(bool _mute)
{
    mute = _mute;
    if (mute)
    {
        Mix_Volume(CH_ALL, 0);
        Mix_VolumeMusic(0);
    }
    else
    {
        Mix_VolumeMusic(MIX_MAX_VOLUME);
        Mix_Volume(CH_ALL, MIX_MAX_VOLUME);
    }
}
