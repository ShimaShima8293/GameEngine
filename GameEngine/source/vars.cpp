#include "vars.h"

namespace GameEngine
{
    Sprite debugText;
    Sprite debugBg;

    SDL_Window* window;
    SDL_Renderer* renderer;


    bool antialiasing = false;

    bool debug;
    bool showBorders;



    bool vsync = true;
}