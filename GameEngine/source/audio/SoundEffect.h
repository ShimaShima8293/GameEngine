#pragma once
#include "internal.h"

#include <string>

struct Mix_Chunk;

namespace GameEngine
{
    class DebugOutput;

    class SoundEffect
    {
    public:
        SoundEffect(std::string path, DebugOutput& output);

        ~SoundEffect();

        void Play();

        const std::string GetPath() const;

    private:
        const std::string path;
        Mix_Chunk* chunk;
        DebugOutput& output;
    };
}