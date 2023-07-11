#include "vars.h"

namespace GameEngine
{
    Entity debugText;
    Entity debugBg;

    SDL_Window* window;
    SDL_Renderer* renderer;

    const std::string DEFAULT_TEXT = "Error";


    bool antialiasing = false;

    bool debug;

    int windowWidth;
    int windowHeight;

    bool vsync = true;
}