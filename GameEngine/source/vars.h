#pragma once

#include <iostream>
#include "macros.h"
#include "Entity.h"
#include <map>
#include <vector>
#include PATH_SDL
#include PATH_SDL_MIXER
#include PATH_SDL_TTF


extern Entity debugText;

extern SDL_Window* window;
extern SDL_Renderer* renderer;

extern const std::string DEFAULT_TEXT;

extern int windowWidth;
extern int windowHeight;

extern bool antialiasing;

extern bool debug;

extern int screenWidth;
extern int screenHeight;

extern bool fullscreen;

extern std::string windowMode;
extern bool mute;
extern bool vsync;