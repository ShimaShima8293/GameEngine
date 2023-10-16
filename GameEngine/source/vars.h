#pragma once

#include "internal.h"
#include "sprite.h"

namespace GameEngine
{
    extern Sprite debugText;
    extern Sprite debugBg;

    extern SDL_Window* window;
    extern SDL_Renderer* renderer;

    extern bool antialiasing;

    extern bool debug;
    extern bool showBorders;

    extern bool vsync;
}