#include "events.h"
#include "vars.h"
#include "audio.h"
#include "scene.h"
#include "animation.h"
#include "render.h"
#include "resource.h"

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
    std::map<Uint8, int> joyAxisPrev;
    std::map<Uint8, int> joyAxis;
    std::map<Uint8, int> joyHat;
    std::map<Uint8, int> joyHatPulse;
    Vec2 cursorPos{};
    bool running = true;
    int globalFrame = 0;
    int gameWidth = 1920;
    int gameHeight = 1080;
    bool fullscreenLocked = false;
    SDL_DisplayMode mode;
    WindowMode windowMode;
    SDL_Cursor* cursor;
    bool disableDebugging = false;
}
using namespace GameEngine;


void processEvents()
{
    SDL_Event event;
    mouseMoved = false;
    keyPressedPulse.clear();
    buttonPressedPulse.clear();
    joyButtonPulse.clear();
    joyHatPulse.clear();
    joyAxisPrev = joyAxis;
    while (SDL_PollEvent(&event))
    {
        if (event.window.event == SDL_WINDOWEVENT_FOCUS_LOST)
        {
            focused = false;
        }
        if (event.window.event == SDL_WINDOWEVENT_FOCUS_GAINED)
        {
            focused = true;
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
        if (event.type == SDL_MOUSEMOTION)
        {
            int cursorX = 0, cursorY = 0;
            SDL_GetMouseState(&cursorX, &cursorY);
            cursorPos = {(float)cursorX, (float)cursorY};
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
            //printInfo((int)event.jbutton.button);
        }
        if (event.type == SDL_JOYBUTTONUP)
        {
            joyButton[event.jbutton.button] = false;
        }
        if (event.type == SDL_JOYAXISMOTION)
        {
            joyAxis[event.jaxis.axis] = event.jaxis.value;
            //printInfo((int)event.jaxis.axis);
        }
        if (event.type == SDL_JOYHATMOTION)
        {
            joyHat[event.jhat.hat] = event.jhat.value;
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
    if (!disableDebugging)
    {
        if (getKeyPressedPulse(SDLK_F3))
        {
            debug = !debug;
        }
        if (getKeyPressedPulse(SDLK_F5))
        {
            showBorders = !showBorders;
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

bool getJoyAxisPulse(int axis, AxisDirection direction, int deadzone)
{
    int prev = joyAxisPrev[axis];
    int curr = joyAxis[axis];

    if (direction == AXIS_POSITIVE)
    {
        if (prev < deadzone && curr > deadzone)
        {
            return true;
        }
    }
    else
    {
        if (prev > -deadzone && curr < -deadzone)
        {
            return true;
        }
    }
    return false;
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
    int width;
    SDL_GetWindowSize(window, &width, nullptr);
    return width;
}

int getWindowHeight()
{
    int height;
    SDL_GetWindowSize(window, nullptr, &height);
    return height;
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
        printError("setSystemCursor: Failed to create a system cursor.");
        printSDLError();
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
        printError("hideCursor: Failed to create a system cursor.");
        printSDLError();
        return -1;
    }
    SDL_SetCursor(cursor);
    return 0;
}

Vec2 getCursorPos()
{
    SDL_Rect destRect = {};

    double gameRatio = (double)getGameWidth() / (double)getGameHeight(); // Calculate the ratio of the game view
    double screenRatio = (double)getWindowWidth() / (double)getWindowHeight(); // Calculate the ratio of the window
    if (gameRatio == screenRatio)
    {
        destRect = { 0, 0, getWindowWidth(), getWindowHeight() };
    }
    else if (gameRatio > screenRatio)
    {
        destRect = { 0, (getWindowHeight() - getGameHeight() * getWindowWidth() / getGameWidth()) / 2, getWindowWidth(), getGameHeight() * getWindowWidth() / getGameWidth() };
    }
    else
    {
        destRect = { (getWindowWidth() - getGameWidth() * getWindowHeight() / getGameHeight()) / 2, 0, getGameWidth() * getWindowHeight() / getGameHeight(), getWindowHeight() };
    }

    float wRatio = (float)getGameWidth() / destRect.w;
    float hRatio = (float)getGameHeight() / destRect.h;
    return Vec2{(cursorPos.x - destRect.x) * wRatio, (cursorPos.y - destRect.y) * hRatio};
}

Vec2 getCursorWindowPos()
{
    return cursorPos;
}

int init(std::string windowTitle, int _gameWidth, int _gameHeight, int initFlags)
{
    if (_gameWidth <= 0)
    {
        printFatalError("init: Parameter `_gameWidth` was smaller than 1.");
        return -1;
    }
    if (_gameHeight <= 0)
    {
        printFatalError("init: Parameter `_gameHeight` was smaller than 1.");
        return -1;
    }
#ifdef _WIN32
    // DPI Aware
    SetProcessDPIAware();
#endif

    srand((unsigned int)(std::time(nullptr)));

    debug = false;
    gameWidth = _gameWidth;
    gameHeight = _gameHeight;

    std::cout << "--- Game Engine Version " GE_VERSION_STR " ---" << "\n";

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        printFatalError("init: Failed to initialize SDL.");
        return -1;
    }
    if (IMG_Init(0) < 0)
    {
        printFatalError("init: Failed to initialize SDL_Image.");
        printSDLError();
        return -1;
    }
    if (TTF_Init() < 0)
    {
        printFatalError("init: Failed to initialize SDL_TTF.");
        printSDLError();
        return -1;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) != 0)
    {
        printFatalError("init: Failed to initialize SDL_Mixer.");
        printSDLError();
        return -1;
    }

    window = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _gameWidth, _gameHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == nullptr)
    {
        printFatalError("init: Failed to create a window.");
        printSDLError();
        return -1;
    }

    if (initFlags & INIT_ANTIALIASING)
    {
        if (SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1") != SDL_TRUE)
        {
            printError("init: Failed to set antialiasing.");
            printSDLError();
        }
        else
        {
            antialiasing = true;
        }
    }

    if (initFlags & INIT_DISABLE_DEBUGGING)
    {
        disableDebugging = true;
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

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);
    SDL_RenderClear(renderer);

    TTF_Font* debugFont = TTF_OpenFont(PATH_DEFAULT_FONT, 24);
    if (debugFont == NULL)
    {
        printError("init: Failed to create `debugFont`.");
        printSDLError();
    }

    debugText.createFromText(DEFAULT_TEXT, debugFont);
    debugText.setPos(0, 0);

    debugBg.createSolid(1, 1, { 0, 0, 0, 128 });

    if (setFullscreenResolution(_gameWidth, _gameHeight) != 0)
    {
        printError("init: Failed to set fullscreen resolution.");
    }

    if (SDL_JoystickOpen(0) == nullptr)
    {
        printInfo("init: Joystick not found.");
    }

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
    if (w <= 0)
    {
        printError("setFullscreenResolution: Parameter `w` was smaller than 1.");
        return -1;
    }
    if (h <= 0)
    {
        printError("setFullscreenResolution: Parameter `h` was smaller than 1.");
        return -1;
    }

    SDL_DisplayMode mode = getDisplayMode();
    mode.w = w;
    mode.h = h;
    if (SDL_SetWindowDisplayMode(window, &mode) != 0)
    {
        printError("setFullscreenResolution: Failed to set window display mode.");
        printSDLError();
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

        processAnimations();

        renderEverything();
    }

    closeResources();
    close();
}
