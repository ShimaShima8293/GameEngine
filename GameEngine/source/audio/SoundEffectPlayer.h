#pragma once

#include "SoundEffect.h"

#include "internal.h"

#include <memory>

namespace GameEngine
{
    class DebugOutput;

    class SoundEffectPlayer
    {
    public:
        SoundEffectPlayer(DebugOutput& output);

        void Play(std::shared_ptr<SoundEffect> soundEffect);

    private:
        std::shared_ptr<SoundEffect> current;
        DebugOutput& output;
    };
}