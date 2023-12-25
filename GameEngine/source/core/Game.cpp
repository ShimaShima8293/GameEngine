#include "Game.h"

namespace GameEngine
{
    Game::Game(int flags)
    {
#ifdef _WIN32
        SetProcessDPIAware();
#endif
        srand((unsigned int)(std::time(nullptr)));

        PrintInfoInternal("Game Engine Version " GE_VERSION_STR);

        if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        {
            PrintFatalErrorInternal("init: Failed to initialize SDL.");
            return;
        }
        if (IMG_Init(0) < 0)
        {
            PrintFatalErrorInternal("init: Failed to initialize SDL_Image.");
            PrintSDLError();
            return;
        }
        if (TTF_Init() < 0)
        {
            PrintFatalErrorInternal("init: Failed to initialize SDL_TTF.");
            PrintSDLError();
            return;
        }
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) != 0)
        {
            PrintFatalErrorInternal("init: Failed to initialize SDL_Mixer.");
            PrintSDLError();
            return;
        }

        TTF_Font* debugFont = TTF_OpenFont(PATH_DEFAULT_FONT, 24);
        if (debugFont == NULL)
        {
            PrintErrorInternal("init: Failed to create `debugFont`.");
            PrintSDLError();
        }

        if (SDL_JoystickOpen(0) == nullptr)
        {
            PrintInfoInternal("init: Joystick not found.");
        }
    }

    Window* Game::MakeWindow(std::string title, int width, int height)
    {
        windows.push_back(Window(title, width, height));
        return &windows.back();
    }

    int Game::SetAntialiasing(bool enableAntialiasing)
    {
        const char* hintInput = enableAntialiasing ? "1" : "0";
        if (SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, hintInput) != SDL_TRUE)
        {
            PrintErrorInternal("Game::SetAntialiasing: Failed to set antialiasing.");
            PrintSDLError();
            return -1;
        }
        this->enableAntialiasing = enableAntialiasing;

        return 0;
    }

    void Game::MainLoop()
    {
        PrintInfo("Game::MainLoop: Entered mainloop");

        while (true)
        {
            for (int i = 0; i < windows.size(); i++)
            {
                windows[i].Update();
            }
        }
    }
}