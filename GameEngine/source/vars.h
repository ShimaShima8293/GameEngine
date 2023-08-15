#pragma once

#include <iostream>
#include "macros.h"
#include "Entity.h"
#include <map>
#include <vector>
#include PATH_SDL
#include PATH_SDL_MIXER
#include PATH_SDL_TTF

namespace GameEngine
{
    extern Entity debugText;
    extern Entity debugBg;

    extern SDL_Window* window;
    extern SDL_Renderer* renderer;

    extern bool antialiasing;

    extern bool debug;
    extern bool exDebug;

    extern int windowWidth;
    extern int windowHeight;

    extern bool vsync;
}