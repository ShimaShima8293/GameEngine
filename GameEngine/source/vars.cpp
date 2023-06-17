#include "vars.h"

namespace GameEngine
{
    Entity debugText;

    SDL_Window* window;
    SDL_Renderer* renderer;

    const std::string DEFAULT_TEXT = "Error";


    bool antialiasing;

    bool debug;

    int windowWidth;
    int windowHeight;

#ifdef NDEBUG
    bool fullscreen = true;
    std::string windowMode = "Full screen";
#else
    bool fullscreen = false;
    std::string windowMode = "Windowed";
#endif

    bool vsync = true;
}