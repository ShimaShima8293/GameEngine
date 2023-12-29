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


    void ProcessEvents()
    {
        SDL_Event event{};
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
                cursorPos = { (float)cursorX, (float)cursorY };
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
                //PrintInfoGE((int)event.jbutton.button);
            }
            if (event.type == SDL_JOYBUTTONUP)
            {
                joyButton[event.jbutton.button] = false;
            }
            if (event.type == SDL_JOYAXISMOTION)
            {
                joyAxis[event.jaxis.axis] = event.jaxis.value;
                //PrintInfoGE((int)event.jaxis.axis);
            }
            if (event.type == SDL_JOYHATMOTION)
            {
                joyHat[event.jhat.hat] = event.jhat.value;
            }
        }
        if (GetKeyPressedPulse(SDLK_F11) && !GetKeyPressed(SDLK_LSHIFT))
        {
            if (GetWindowMode() != WINDOW_FULLSCREEN)
            {
                SetWindowMode(WINDOW_FULLSCREEN);
            }
            else
            {
                SetWindowMode(WINDOW_WINDOWED);
            }
        }
        if (GetKeyPressedPulse(SDLK_F11) && GetKeyPressed(SDLK_LSHIFT))
        {
            if (GetWindowMode() != WINDOW_FULLSCREEN_DESKTOP)
            {
                SetWindowMode(WINDOW_FULLSCREEN_DESKTOP);
            }
            else
            {
                SetWindowMode(WINDOW_WINDOWED);
            }
        }
        if (!disableDebugging)
        {
            if (GetKeyPressedPulse(SDLK_F3))
            {
                debug = !debug;
            }
            if (GetKeyPressedPulse(SDLK_F5))
            {
                showBorders = !showBorders;
            }
            if (GetKeyPressedPulse(SDLK_m))
            {
                SetMuteState(!GetMuteState());
            }
            if (GetKeyPressedPulse(SDLK_F4))
            {
                ReloadCurrentScene();
            }
        }
    }

    bool GetMouseMoved()
    {
        return mouseMoved;
    }

    bool GetWindowFocus()
    {
        return focused;
    }

    bool GetKeyPressed(SDL_KeyCode code)
    {
        return keyPressed[code];
    }

    bool GetKeyPressedPulse(SDL_KeyCode code)
    {
        return keyPressedPulse[code];
    }

    bool GetJoyButton(int button)
    {
        return joyButton[button];
    }

    bool GetJoyButtonPulse(int button)
    {
        return joyButtonPulse[button];
    }

    int GetJoyAxis(int axis)
    {
        return joyAxis[axis];
    }

    bool GetJoyAxisPulse(int axis, AxisDirection direction, int deadzone)
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

    bool GetMouseButton(int button)
    {
        return buttonPressed[button];
    }

    bool GetMouseButtonPulse(int button)
    {
        return buttonPressedPulse[button];
    }

    bool GetRunning()
    {
        return running;
    }

    void EndMainloop()
    {
        running = false;
    }

    void Close()
    {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
        SDL_DestroyWindow(window);
        window = nullptr;
        SDL_Quit();
    }

    int GetGameWidth()
    {
        return gameWidth;
    }

    int GetGameHeight()
    {
        return gameHeight;
    }

    SDL_Window* GetWindow()
    {
        return window;
    }

    SDL_Renderer* GetRenderer()
    {
        return renderer;
    }

    int GetWindowWidth()
    {
        int width;
        SDL_GetWindowSize(window, &width, nullptr);
        return width;
    }

    int GetWindowHeight()
    {
        int height;
        SDL_GetWindowSize(window, nullptr, &height);
        return height;
    }

    void SetWindowMode(WindowMode mode)
    {
        SDL_SetWindowFullscreen(window, mode);
        windowMode = mode;
    }

    WindowMode GetWindowMode()
    {
        return windowMode;
    }

    int SetSystemCursor(SDL_SystemCursor _cursor)
    {
        if (cursor != nullptr)
        {
            SDL_FreeCursor(cursor);
        }
        cursor = SDL_CreateSystemCursor(_cursor);
        if (cursor == nullptr)
        {
            PrintErrorGE("SetSystemCursor: Failed to create a system cursor.");
            PrintSDLError();
            return -1;
        }
        SDL_SetCursor(cursor);
        return 0;
    }

    int HideCursor()
    {
        if (cursor != nullptr)
        {
            SDL_FreeCursor(cursor);
        }
        int32_t cursorData[2] = { 0, 0 };
        cursor = SDL_CreateCursor((Uint8*)cursorData, (Uint8*)cursorData, 8, 8, 4, 4);
        if (cursor == nullptr)
        {
            PrintErrorGE("HideCursor: Failed to create a system cursor.");
            PrintSDLError();
            return -1;
        }
        SDL_SetCursor(cursor);
        return 0;
    }

    Vec2 GetCursorPos()
    {
        SDL_Rect destRect = {};

        double gameRatio = (double)GetGameWidth() / (double)GetGameHeight(); // Calculate the ratio of the game view
        double screenRatio = (double)GetWindowWidth() / (double)GetWindowHeight(); // Calculate the ratio of the window
        if (gameRatio == screenRatio)
        {
            destRect = { 0, 0, GetWindowWidth(), GetWindowHeight() };
        }
        else if (gameRatio > screenRatio)
        {
            destRect = { 0, (GetWindowHeight() - GetGameHeight() * GetWindowWidth() / GetGameWidth()) / 2, GetWindowWidth(), GetGameHeight() * GetWindowWidth() / GetGameWidth() };
        }
        else
        {
            destRect = { (GetWindowWidth() - GetGameWidth() * GetWindowHeight() / GetGameHeight()) / 2, 0, GetGameWidth() * GetWindowHeight() / GetGameHeight(), GetWindowHeight() };
        }

        float wRatio = (float)GetGameWidth() / destRect.w;
        float hRatio = (float)GetGameHeight() / destRect.h;
        return Vec2{ (cursorPos.x - destRect.x) * wRatio, (cursorPos.y - destRect.y) * hRatio };
    }

    Vec2 GetCursorWindowPos()
    {
        return cursorPos;
    }

    int Init(std::string windowTitle, int _gameWidth, int _gameHeight, int initFlags)
    {
        if (_gameWidth <= 0)
        {
            PrintFatalErrorGE("Init: Parameter `_gameWidth` was smaller than 1.");
            return -1;
        }
        if (_gameHeight <= 0)
        {
            PrintFatalErrorGE("Init: Parameter `_gameHeight` was smaller than 1.");
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

        PrintInfoGE("Game Engine Version " GE_VERSION_STR);

        if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        {
            PrintFatalErrorGE("Init: Failed to initialize SDL.");
            return -1;
        }
        if (IMG_Init(0) < 0)
        {
            PrintFatalErrorGE("Init: Failed to initialize SDL_Image.");
            PrintSDLError();
            return -1;
        }
        if (TTF_Init() < 0)
        {
            PrintFatalErrorGE("Init: Failed to initialize SDL_TTF.");
            PrintSDLError();
            return -1;
        }
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) != 0)
        {
            PrintFatalErrorGE("Init: Failed to initialize SDL_Mixer.");
            PrintSDLError();
            return -1;
        }

        window = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _gameWidth, _gameHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
        if (window == nullptr)
        {
            PrintFatalErrorGE("Init: Failed to create a window.");
            PrintSDLError();
            return -1;
        }

        if (initFlags & INIT_ANTIALIASING)
        {
            if (SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1") != SDL_TRUE)
            {
                PrintErrorGE("Init: Failed to set antialiasing.");
                PrintSDLError();
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
            PrintErrorGE("Init: Failed to create `debugFont`.");
            PrintSDLError();
        }

        debugText.CreateFromText(DEFAULT_TEXT, debugFont);
        debugText.SetPos(0, 0);

        debugBg.CreateSolid(1, 1, { 0, 0, 0, 128 });

        if (SetFullscreenResolution(_gameWidth, _gameHeight) != 0)
        {
            PrintErrorGE("Init: Failed to set fullscreen resolution.");
        }

        if (SDL_JoystickOpen(0) == nullptr)
        {
            PrintInfoGE("Init: Joystick not found.");
        }

        running = true;

        return 0;
    }

    SDL_DisplayMode GetDisplayMode()
    {
        SDL_GetWindowDisplayMode(window, &mode);
        return mode;
    }

    int SetFullscreenResolution(int w, int h)
    {
        if (w <= 0)
        {
            PrintErrorGE("SetFullscreenResolution: Parameter `w` was smaller than 1.");
            return -1;
        }
        if (h <= 0)
        {
            PrintErrorGE("SetFullscreenResolution: Parameter `h` was smaller than 1.");
            return -1;
        }

        SDL_DisplayMode mode = GetDisplayMode();
        mode.w = w;
        mode.h = h;
        if (SDL_SetWindowDisplayMode(window, &mode) != 0)
        {
            PrintErrorGE("SetFullscreenResolution: Failed to set window display mode.");
            PrintSDLError();
            return -1;
        }
        return 0;
    }

    GE_HWND GetHWND()
    {
#ifdef _WIN32
        SDL_SysWMinfo wmInfo{};
        SDL_VERSION(&wmInfo.version);
        SDL_GetWindowWMInfo(GetWindow(), &wmInfo);
        HWND hwnd = wmInfo.info.win.window;
        return hwnd;
#else
        PrintErrorGE("GetHWND: Unsupported OS.");
        return nullptr;
#endif
    }

    void Mainloop()
    {
        while (GetRunning())
        {
            ProcessEvents();

            if (!GetWindowFocus())
            {
                SDL_Delay(1000 / 60);
                continue;
            }

            ProcessScene();

            ProcessAnimations();

            RenderEverything();
        }

        CloseResources();
        Close();
    }

}