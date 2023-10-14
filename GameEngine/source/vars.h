#pragma once

#include <iostream>
#include "macros.h"
#include "sprite.h"
#include <map>
#include <vector>
#include PATH_SDL
#include PATH_SDL_MIXER
#include PATH_SDL_TTF

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