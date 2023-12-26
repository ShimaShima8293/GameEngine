#pragma once
#include "core/internal.h"

namespace GameEngine
{
    class Renderer
    {
    public:
        Renderer();

    private:
        SDL_Renderer* renderer;
    };
}