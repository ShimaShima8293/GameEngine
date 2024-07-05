#include "MusicPlayer.h"

#include <SDL_mixer.h>

namespace GameEngine
{
    MusicPlayer::MusicPlayer() :
        MusicPlayer("")
    {
    }
    
    MusicPlayer::MusicPlayer(std::string namePrefix) :
        music(nullptr),
        cut(nullptr),
        wrap(nullptr),
        namePrefix(namePrefix)
    {
    }

    MusicPlayer::~MusicPlayer()
    {
        Free();
    }

    void MusicPlayer::PlayMusic(std::string name, bool loop)
    {
        Free();

        //music = OpenMusic(namePrefix + name + ".wav");

        if (loop)
        {
            Mix_PlayMusic(music, -1);
        }
        else
        {
            Mix_PlayMusic(music, 0);
        }
    }

    void MusicPlayer::PlayMusicSet(std::string name)
    {
        std::string cutName = namePrefix + name + "_cut";
        std::string wrapName = namePrefix + name + "_wrap";

        this->PlayMusicSet(cutName, wrapName);
    }

    void MusicPlayer::PlayMusicSet(std::string cutName, std::string wrapName)
    {
        Free();

        //cut = OpenWAV(namePrefix + cutName + "_cut.wav");
        //wrap = OpenWAV(namePrefix + wrapName + "_wrap.wav");

        //GameEngine::PlayMusicSet(cut, wrap);
    }

    void MusicPlayer::FadeOut(int ms)
    {
        //FadeOutMusic(ms);
    }

    void MusicPlayer::StopMusic()
    {
        Mix_HaltMusic();
        //Mix_HaltChannel(CH_INTRO);
        //Mix_HaltChannel(CH_LOOP);
    }

    void MusicPlayer::Free()
    {
        StopMusic();

        if (music != nullptr)
        {
            //CloseMusic(music);
        }
        if (cut != nullptr)
        {
            //CloseWAV(cut);
        }
        if (wrap != nullptr)
        {
            //CloseWAV(wrap);
        }
    }
}