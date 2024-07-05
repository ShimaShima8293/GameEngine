#include "SoundEffect.h"

#include "debugging/DebugOutput.h"

#include <SDL_mixer.h>

namespace GameEngine
{
    SoundEffect::SoundEffect(std::string path, DebugOutput& output) :
        path(path),
        chunk(nullptr),
        output(output)
    {
        if (chunk == nullptr)
        {
            output.ErrorGE("SoundEffect::SoundEffect: Parameter `chunk` was nullptr.");
            return;
        }
    }

    SoundEffect::~SoundEffect()
    {
        if (chunk == nullptr)
        {
            return;
        }

        Mix_FreeChunk(chunk);
    }

    void SoundEffect::Play()
    {
        if (chunk == nullptr)
        {
            output.ErrorGE("SoundEffect::Play: Member `chunk` was nullptr.");
            return;
        }

        Mix_PlayChannel(-1, chunk, 0);
    }

    const std::string SoundEffect::GetPath() const
    {
        return path;
    }
}