#include "audio.h"
#include "vars.h"

namespace GameEngine
{
    bool mute = false;

    void playMusicSet(Mix_Chunk* intro, Mix_Chunk* loop, int fade)
    {
        if (intro == nullptr)
        {
            printError("playMusicSet: Parameter `intro` was nullptr.");
            return;
        }
        if (intro == nullptr)
        {
            printError("playMusicSet: Parameter `loop` was nullptr.");
            return;
        }
        haltMusic();
        if (Mix_PlayChannel(CH_INTRO, intro, 0) == -1)
        {
            printError("playMusicSet: Failed to play an intro WAV chunk.");
            printSDLError();
            return;
        }
        Mix_FadeOutChannel(CH_INTRO, fade);

        if (Mix_FadeInChannel(CH_LOOP, loop, -1, fade) == -1)
        {
            printError("playMusicSet: Failed to play a loop WAV chunk.");
            printSDLError();
            return;
        };
    }

    void playSoundEffect(Mix_Chunk* chunk)
    {
        if (chunk == nullptr)
        {
            printError("playSoundEffect: Parameter `chunk` was nullptr.");
            return;
        }
        if (Mix_PlayChannel(CH_FX, chunk, 0) == -1)
        {
            printError("playSoundEffect: Failed to play a sound effect WAV chunk.");
            printSDLError();
            return;
        }
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

}