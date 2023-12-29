#include "audio.h"
#include "vars.h"

namespace GameEngine
{
    bool mute = false;

    void PlayMusicSet(Mix_Chunk* intro, Mix_Chunk* loop, int fade)
    {
        if (intro == nullptr)
        {
            PrintErrorGE("PlayMusicSet: Parameter `intro` was nullptr.");
            return;
        }
        if (intro == nullptr)
        {
            PrintErrorGE("PlayMusicSet: Parameter `loop` was nullptr.");
            return;
        }
        HaltMusic();
        if (Mix_PlayChannel(CH_INTRO, intro, 0) == -1)
        {
            PrintErrorGE("PlayMusicSet: Failed to play an intro WAV chunk.");
            PrintSDLError();
            return;
        }
        Mix_FadeOutChannel(CH_INTRO, fade);

        if (Mix_FadeInChannel(CH_LOOP, loop, -1, fade) == -1)
        {
            PrintErrorGE("PlayMusicSet: Failed to play a loop WAV chunk.");
            PrintSDLError();
            return;
        };
    }

    void PlaySoundEffect(Mix_Chunk* chunk)
    {
        if (chunk == nullptr)
        {
            PrintErrorGE("PlaySoundEffect: Parameter `chunk` was nullptr.");
            return;
        }
        if (Mix_PlayChannel(CH_FX, chunk, 0) == -1)
        {
            PrintErrorGE("PlaySoundEffect: Failed to play a sound effect WAV chunk.");
            PrintSDLError();
            return;
        }
    }

    void HaltMusic()
    {
        Mix_HaltChannel(CH_INTRO);
        Mix_HaltChannel(CH_LOOP);
    }

    void FadeOutMusic(int fade)
    {
        Mix_FadeOutChannel(CH_INTRO, fade);
        Mix_FadeOutChannel(CH_LOOP, fade);
    }

    bool GetMuteState()
    {
        return mute;
    }

    void SetMuteState(bool _mute)
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