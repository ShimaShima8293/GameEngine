#include "SoundEffectManager.h"

namespace GameEngine
{
    SoundEffectManager::SoundEffectManager(std::string namePrefix, DebugOutput& output) :
        namePrefix(namePrefix),
        soundEffects(),
        output(output)
    {
    }

    void SoundEffectManager::Play(std::string name)
    {
        for (SoundEffect& soundEffect : soundEffects)
        {
            if (soundEffect.GetPath() == GetPath(name))
            {
                soundEffect.Play();
                return;
            }
        }

        soundEffects.emplace_back(GetPath(name), output).Play();
    }

    std::string SoundEffectManager::GetPath(std::string name) const
    {
        return namePrefix + name + ".wav";
    }
}