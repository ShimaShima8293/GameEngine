#include "ResourceManager.h"
#include "debugging/DebugOutput.h"

namespace GameEngine
{
    ResourceManager::ResourceManager(std::string fontPath, std::string soundEffectPathPrefix, DebugOutput& output) :
        fontManager(fontPath, output),
        soundEffectManager(soundEffectPathPrefix, output),
        output(output)
    {
    }

    Font& ResourceManager::GetFont(int size, FontAlign align)
    {
        return fontManager.Get(size, align);
    }
}