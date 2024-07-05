#pragma once
#include "internal.h"
#include <string>

typedef struct _Mix_Music Mix_Music;
struct Mix_Chunk;

namespace GameEngine
{
    class MusicPlayer
    {
    public:
        MusicPlayer();

        MusicPlayer(std::string namePrefix);

        ~MusicPlayer();

        void PlayMusic(std::string name, bool loop = true);

        void PlayMusicSet(std::string name);

        void PlayMusicSet(std::string cutName, std::string wrapName);

        void FadeOut(int ms);

        void StopMusic();

        void Free();

    private:
        std::string namePrefix;
        Mix_Music* music;
        Mix_Chunk* cut;
        Mix_Chunk* wrap;
    };
}