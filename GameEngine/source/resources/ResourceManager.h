#pragma once
#include "internal.h"
#include "FontManager.h"
#include "SoundEffectManager.h"

#include <memory>

namespace GameEngine
{
    class DebugOutput;

    class ResourceManager
    {
    public:
        ResourceManager(std::string fontPath, std::string soundEffectPathPrefix, DebugOutput& output);

        Font& GetFont(int size, FontAlign align = FONT_ALIGN_LEFT);

        //SoundEffect& GetSoundEffect(int index);
        //SoundEffect& GetSoundEffect(std::string path);

    private:
        FontManager fontManager;
        SoundEffectManager soundEffectManager;
        DebugOutput& output;
    };
}