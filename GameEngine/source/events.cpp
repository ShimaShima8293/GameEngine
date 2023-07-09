#include "events.h"
#include <map>
#include "vars.h"
#include "audio.h"
#include "scene.h"
#include "update.h"
#include "animation.h"
#include "render.h"
#include "resource.h"
#ifdef _WIN32
#include <Windows.h>
#endif

namespace GameEngine
{
    bool focused = false;
    bool mouseMoved = false;
    std::map<SDL_Keycode, bool> keyPressed;
    std::map<SDL_Keycode, bool> keyPressedPulse;
    std::map<Uint8, bool> buttonPressed;
    std::map<Uint8, bool> buttonPressedPulse;
    std::map<Uint8, bool> joyPressed;
    std::map<Uint8, bool> joyPressedPulse;
    int mouseX = 0, mouseY = 0;
    bool running = true;
    int globalFrame = 0;
    int gameWidth = 1920;
    int gameHeight = 1080;
    bool fullscreenLocked = false;
    SDL_DisplayMode mode;
    WindowMode windowMode;
    SDL_Cursor* cursor;
}
using namespace GameEngine;


void processEvents()
{
    SDL_Event event;
    mouseMoved = false;
    keyPressedPulse.clear();
    buttonPressedPulse.clear();
    while (SDL_PollEvent(&event))
    {
        if (event.window.event == SDL_WINDOWEVENT_FOCUS_LOST)
        {
            focused = false;
            printInfo("Focus lost");
        }
        if (event.window.event == SDL_WINDOWEVENT_FOCUS_GAINED)
        {
            focused = true;
            printInfo("Focus gained");
        }
        if (event.type == SDL_QUIT)
        {
            running = false;
        }
        if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
        {
            keyPressed[event.key.keysym.sym] = true;
            keyPressedPulse[event.key.keysym.sym] = true;
        }
        if (event.type == SDL_KEYUP)
        {
            keyPressed[event.key.keysym.sym] = false;
        }
        if (event.type == 8192 || event.window.event == SDL_WINDOWEVENT_FOCUS_GAINED)
        {
            SDL_GetWindowSize(window, &windowWidth, &windowHeight);
            printInfo("Window resolution changed to " + std::to_string(windowWidth) + "x" + std::to_string(windowHeight));
        }
        if (event.type == SDL_MOUSEMOTION)
        {
            SDL_GetMouseState(&mouseX, &mouseY);
            mouseMoved = true;
        }
        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            buttonPressed[event.button.button] = true;
            buttonPressedPulse[event.button.button] = true;
        }
        if (event.type == SDL_MOUSEBUTTONUP)
        {
            buttonPressed[event.button.button] = false;
        }
        if (event.type == SDL_JOYBUTTONDOWN)
        {
            joyPressed[event.jbutton.button] = true;
            printInfo(event.jbutton.button);
        }
        if (event.type == SDL_JOYBUTTONUP)
        {
            joyPressed[event.jbutton.button] = false;
            printInfo(event.jbutton.button);
        }
    }

    if (getKeyPressedPulse(SDLK_F11) && !getKeyPressed(SDLK_LSHIFT))
    {
        if (getWindowMode() != WINDOW_FULLSCREEN)
        {
            setWindowMode(WINDOW_FULLSCREEN);
        }
        else
        {
            setWindowMode(WINDOW_WINDOWED);
        }
    }
    if (getKeyPressedPulse(SDLK_F11) && getKeyPressed(SDLK_LSHIFT))
    {
        if (getWindowMode() != WINDOW_FULLSCREEN_DESKTOP)
        {
            setWindowMode(WINDOW_FULLSCREEN_DESKTOP);
        }
        else
        {
            setWindowMode(WINDOW_WINDOWED);
        }
    }
    if (getKeyPressedPulse(SDLK_F3))
    {
        debug = !debug;
    }
    if (getKeyPressedPulse(SDLK_m))
    {
        setMuteState(!getMuteState());
    }

    if (getKeyPressedPulse(SDLK_F4))
    {
        reloadCurrentScene();
    }
}

bool getWindowFocus()
{
    return focused;
}

bool getKeyPressed(SDL_KeyCode code)
{
    return keyPressed[code];
}

bool getKeyPressedPulse(SDL_KeyCode code)
{
    return keyPressedPulse[code];
}

bool getRunning()
{
    return running;
}

void endMainloop()
{
    running = false;
}

void close()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int getGameWidth()
{
    return gameWidth;
}

int getGameHeight()
{
    return gameHeight;
}

SDL_Window* getWindow()
{
    return window;
}

SDL_Renderer* getRenderer()
{
    return renderer;
}

int getWindowWidth()
{
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);
    return windowWidth;
}

int getWindowHeight()
{
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);
    return windowHeight;
}

void setWindowMode(WindowMode mode)
{
    SDL_SetWindowFullscreen(window, mode);
    windowMode = mode;
}

WindowMode getWindowMode()
{
    return windowMode;
}

void setSystemCursor(SDL_SystemCursor _cursor)
{
    if (cursor != nullptr)
    {
        SDL_FreeCursor(cursor);
    }
    cursor = SDL_CreateSystemCursor(_cursor);
    if (cursor == nullptr)
    {
        printError("setSystemCursor: Failed to create a system cursor. SDL error: " << SDL_GetError());
        return;
    }
    SDL_SetCursor(cursor);
}

void hideCursor()
{
    if (cursor != nullptr)
    {
        SDL_FreeCursor(cursor);
    }
    int32_t cursorData[2] = { 0, 0 };
    cursor = SDL_CreateCursor((Uint8*)cursorData, (Uint8*)cursorData, 8, 8, 4, 4);
    if (cursor == nullptr)
    {
        printError("hideCursor: Failed to create a system cursor. SDL error: " << SDL_GetError());
        return;
    }
    SDL_SetCursor(cursor);
}

void init(std::string windowTitle, int _gameWidth, int _gameHeight, int _windowFlags, bool _debug, bool renderQuality)
{
#ifdef _WIN32
    // DPI Aware
    SetProcessDPIAware();
#endif

    srand((unsigned int)(std::time(nullptr)));

    debug = _debug;
    gameWidth = _gameWidth;
    gameHeight = _gameHeight;

    printInfo("Game Engine Version " << GE_VERSION_MAJOR << "." << GE_VERSION_MINOR << "." << GE_VERSION_PATCH);

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        printFatalError("Failed to initialize SDL... SDL Error: " << SDL_GetError());
    }
    if (IMG_Init(0) < 0)
    {
        printFatalError("Failed to initialize SDL_Image... SDL_image Error: " << IMG_GetError());
    }
    if (TTF_Init() < 0)
    {
        printFatalError("Failed to initialize SDL_TTF... SDL_ttf Error: " << TTF_GetError());
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) != 0)
    {
        printFatalError("Failed to initialize SDL_Mixer... SDL_mixer Error: " << Mix_GetError());
    }

    window = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _gameWidth, _gameHeight, _windowFlags);

    if (renderQuality)
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    antialiasing = renderQuality;

    SDL_GetWindowDisplayMode(window, &mode);
    mode.refresh_rate = 60;
    SDL_SetWindowDisplayMode(window, &mode);

    SDL_GetWindowDisplayMode(window, &mode);
    if (mode.refresh_rate == 60)
    {
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        vsync = true;
    }
    else
    {
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        vsync = false;
    }

    printInfo("Display Info");
    printInfo("  - Width: " << mode.w << " pixels");
    printInfo("  - Height: " << mode.h << " pixels");
    printInfo("  - Refresh rate: " << (mode.refresh_rate == 0 ? "VSync not supported" : (std::to_string(mode.refresh_rate) + " frames per second").c_str()));
    printInfo("  - Supports VSync: " << (mode.refresh_rate == 0 ? "No" : "Yes"));
    printInfo("  - VSync: " << (vsync ? "On (60 fps)" : "Off (not 60fps)"));
    printInfo("SDL Versions");
    printInfo("  - SDL version: " << SDL_MAJOR_VERSION << "." << SDL_MINOR_VERSION << "." << SDL_PATCHLEVEL);
    printInfo("  - SDL_image version: " << SDL_IMAGE_MAJOR_VERSION << "." << SDL_IMAGE_MINOR_VERSION << "." << SDL_IMAGE_PATCHLEVEL);
    printInfo("  - SDL_ttf version: " << SDL_TTF_MAJOR_VERSION << "." << SDL_TTF_MINOR_VERSION << "." << SDL_TTF_PATCHLEVEL);
    printInfo("  - SDL_mixer version: " << SDL_MIXER_MAJOR_VERSION << "." << SDL_MIXER_MINOR_VERSION << "." << SDL_MIXER_PATCHLEVEL);


    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);
    SDL_RenderClear(renderer);

    TTF_Font* debugFont = TTF_OpenFont("/Windows/Fonts/arial.ttf", 40);
    if (debugFont == NULL)
    {
        printFatalError("Failed to create debugFont");
    }

    debugText.setName("debugText");
    debugText.loadFromText(DEFAULT_TEXT, debugFont);
    debugText.setPos(0, 0);

    running = true;
}

SDL_DisplayMode getDisplayMode()
{
    SDL_GetWindowDisplayMode(window, &mode);
    return mode;
}

void setFullscreenResolution(int w, int h)
{
    if (w <= 0 || h <= 0)
    {
        printError("setFullscreenResolution: w or h cannot be smaller than 1.");
    }
    SDL_DisplayMode mode = getDisplayMode();
    mode.w = w;
    mode.h = h;
    if (SDL_SetWindowDisplayMode(window, &mode) != 0)
    {
        printError("setFullscreenResolution: failed to set window display mode. SDL error: " << SDL_GetError());
    }
}

void startMainloop()
{
    while (getRunning())
    {
        processEvents();

        if (!getWindowFocus())
        {
            SDL_Delay(1000 / 60);
            continue;
        }

        processScene();

        processUpdates();

        processAnimations();

        renderEverything();
    }

    closeResources();
    close();
}