#pragma once

#include "audio/SoundEffect.h"
#include "internal.h"

#include <string>
#include <vector>

namespace GameEngine
{
    class DebugOutput;

    class SoundEffectManager
    {
    public:
        SoundEffectManager(std::string namePrefix, DebugOutput& output);

        void Play(std::string name);

    private:
        std::string GetPath(std::string name) const;

        std::string namePrefix;

        std::vector<SoundEffect> soundEffects;

        DebugOutput& output;
    };
}