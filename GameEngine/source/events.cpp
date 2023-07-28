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
    std::map<Uint8, bool> joyButton;
    std::map<Uint8, bool> joyButtonPulse;
    std::map<Uint8, int> joyAxis;
    std::map<Uint8, bool> joyAxisPulse;
    std::map<Uint8, int> joyHat;
    std::map<Uint8, int> joyHatPulse;
    int mouseX = 0, mouseY = 0;
    bool running = true;
    int globalFrame = 0;
    int gameWidth = 1920;
    int gameHeight = 1080;
    bool fullscreenLocked = false;
    SDL_DisplayMode mode;
    WindowMode windowMode;
    SDL_Cursor* cursor;
    bool disableDefaultKeyBindings = false;
}
using namespace GameEngine;


void processEvents()
{
    SDL_Event event;
    mouseMoved = false;
    keyPressedPulse.clear();
    buttonPressedPulse.clear();
    joyButtonPulse.clear();
    joyAxisPulse.clear();
    joyHatPulse.clear();
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
            joyButton[event.jbutton.button] = true;
            joyButtonPulse[event.jbutton.button] = true;
            printInfo((int)event.jbutton.button);
        }
        if (event.type == SDL_JOYBUTTONUP)
        {
            joyButton[event.jbutton.button] = false;
        }
        if (event.type == SDL_JOYAXISMOTION)
        {
            joyAxis[event.jaxis.axis] = event.jaxis.value;
            joyAxisPulse[event.jaxis.axis] = true;
            //printInfo((int)event.jaxis.axis);
        }
        if (event.type == SDL_JOYHATMOTION)
        {
            joyHat[event.jhat.hat] = event.jhat.value;
        }
    }
    if (!disableDefaultKeyBindings)
    {
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
            if (debug && getKeyPressed(SDLK_LSHIFT))
            {
                exDebug = true;
            }
            else
            {
                exDebug = false;
            }
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

bool getJoyButton(int button)
{
    return joyButton[button];
}

bool getJoyButtonPulse(int button)
{
    return joyButtonPulse[button];
}

int getJoyAxis(int axis)
{
    return joyAxis[axis];
}

bool getJoyAxisPulse(int axis)
{
    return joyAxisPulse[axis];
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
    renderer = nullptr;
    SDL_DestroyWindow(window);
    window = nullptr;
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

int setSystemCursor(SDL_SystemCursor _cursor)
{
    if (cursor != nullptr)
    {
        SDL_FreeCursor(cursor);
    }
    cursor = SDL_CreateSystemCursor(_cursor);
    if (cursor == nullptr)
    {
        printError("setSystemCursor: Failed to create a system cursor. SDL error: " << SDL_GetError());
        return -1;
    }
    SDL_SetCursor(cursor);
    return 0;
}

int hideCursor()
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
        return -1;
    }
    SDL_SetCursor(cursor);
    return 0;
}

int init(std::string windowTitle, int _gameWidth, int _gameHeight, int initFlags)
{
#ifdef _WIN32
    // DPI Aware
    SetProcessDPIAware();
#endif

    srand((unsigned int)(std::time(nullptr)));

    debug = false;
    gameWidth = _gameWidth;
    gameHeight = _gameHeight;

    printInfo("Game Engine Version " << GE_VERSION_MAJOR << "." << GE_VERSION_MINOR << "." << GE_VERSION_PATCH);

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        printFatalError("init: Failed to initialize SDL. SDL Error: " << SDL_GetError());
        return -1;
    }
    if (IMG_Init(0) < 0)
    {
        printFatalError("init: Failed to initialize SDL_Image. SDL_image Error: " << IMG_GetError());
        return -1;
    }
    if (TTF_Init() < 0)
    {
        printFatalError("init: Failed to initialize SDL_TTF. SDL_ttf Error: " << TTF_GetError());
        return -1;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) != 0)
    {
        printFatalError("init: Failed to initialize SDL_Mixer. SDL_mixer Error: " << Mix_GetError());
        return -1;
    }

    window = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _gameWidth, _gameHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == nullptr)
    {
        printFatalError("init: Failed to create a window. SDL Error: " << SDL_GetError());
        return -1;
    }

    if (initFlags & INIT_ANTIALIASING)
    {
        if (SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1") != SDL_TRUE)
        {
            printError("init: Failed to set antialiasing. SDL Error: " << SDL_GetError());
        }
        else
        {
            antialiasing = true;
        }
    }

    if (initFlags & INIT_DISABLE_DEFAULT_KEYBINDINGS)
    {
        disableDefaultKeyBindings = true;
    }

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

    TTF_Font* debugFont = TTF_OpenFont("/Windows/Fonts/arial.ttf", 24);
    if (debugFont == NULL)
    {
        printError("init: Failed to create debugFont. SDL error: " << TTF_GetError());
    }

    debugText.createFromText(DEFAULT_TEXT, debugFont);
    debugText.setPos(0, 0);

    debugBg.createSolid(1, 1, { 0, 0, 0, 128 });

    if (setFullscreenResolution(_gameWidth, _gameHeight) != 0)
    {
        printFatalError("init: Failed to set fullscreen resolution.");
    }

    SDL_JoystickOpen(0);

    running = true;

    return 0;
}

SDL_DisplayMode getDisplayMode()
{
    SDL_GetWindowDisplayMode(window, &mode);
    return mode;
}

int setFullscreenResolution(int w, int h)
{
    if (w <= 0 || h <= 0)
    {
        printError("setFullscreenResolution: w or h cannot be smaller than 1.");
        return -1;
    }
    SDL_DisplayMode mode = getDisplayMode();
    mode.w = w;
    mode.h = h;
    if (SDL_SetWindowDisplayMode(window, &mode) != 0)
    {
        printError("setFullscreenResolution: failed to set window display mode. SDL error: " << SDL_GetError());
        return -1;
    }
    return 0;
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