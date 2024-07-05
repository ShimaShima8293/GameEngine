#include "SoundEffectPlayer.h"
#include "debugging/DebugOutput.h"

namespace GameEngine
{
    SoundEffectPlayer::SoundEffectPlayer(DebugOutput& output) :
        output(output)
    {
        
    }

    void SoundEffectPlayer::Play(std::shared_ptr<SoundEffect> soundEffect)
    {
        soundEffect->Play();

        current = soundEffect;
    }
}