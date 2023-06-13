#include "vars.h"

Entity debugText;

SDL_Window* window;
SDL_Renderer* renderer;

const std::string DEFAULT_TEXT = "Error";
int windowWidth = 2880;
int windowHeight = 1800;

bool antialiasing;

bool debug;

int screenWidth;
int screenHeight;

#ifdef NDEBUG
bool fullscreen = true;
std::string windowMode = "Full screen";
#else
bool fullscreen = false;
std::string windowMode = "Windowed";
#endif

bool musicOff = false;
bool vsync = true;
