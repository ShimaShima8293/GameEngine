#include "audio.h"
#include "vars.h"

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
    return musicOff;
}

void setMuteState(bool _mute)
{
    musicOff = _mute;
}
