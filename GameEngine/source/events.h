#pragma once

#include "internal.h"
#include "utilities.h"

#ifdef _WIN32
#include <SDL_syswm.h>
#define GE_HWND HWND
#else
#define GE_HWND void*
#endif

namespace GameEngine
{
    typedef enum WindowMode
    {
        WINDOW_WINDOWED = 0,
        WINDOW_FULLSCREEN = 1,
        WINDOW_FULLSCREEN_DESKTOP = 4097
    } WindowMode;

    enum AxisDirection
    {
        AXIS_POSITIVE,
        AXIS_NEGATIVE
    };

    // Processes events. Updates `KeyPressed` and `KeyPressedPulse`.
    void ProcessEvents();

    bool GetMouseMoved();

    // Get if the window is focused.
    // \returns bool True if the window is focused; False if not.
    bool GetWindowFocus();

    // Get if a key is pressed.
    // \param code The key code from SDL_KeyCode.
    // \returns bool True if the requested key is pressed down.
    bool GetKeyPressed(SDL_KeyCode code);

    // Get if a key is pressed. It is similar to `GetKeyPressed()` but this function will only return true when the requested key got pressed on current frame.
    // \param code The key code from SDL_KeyCode.
    // \returns bool True if the requested key is pressed down on current frame.
    bool GetKeyPressedPulse(SDL_KeyCode code);

    // Get if a joycon button is pressed.
    // \param button The index of the button.
    // \returns bool True if the requested button is pressed down.
    bool GetJoyButton(int button);

    // Get if a joycon button is pressed.
    // \param button The index of the button.
    // \returns bool True if the requested button is pressed down.
    bool GetJoyButtonPulse(int button);

    int GetJoyAxis(int axis);

    bool GetJoyAxisPulse(int axis, AxisDirection direction, int deadzone);

    bool GetMouseButton(int button);

    bool GetMouseButtonPulse(int button);

    bool GetRunning();

    void EndMainloop();

    // Frees things and quits SDL.
    void Close();

    int GetGameWidth();

    int GetGameHeight();

    SDL_Window* GetWindow();

    SDL_Renderer* GetRenderer();

    int GetWindowWidth();

    int GetWindowHeight();

    void SetWindowMode(WindowMode mode);

    WindowMode GetWindowMode();

    int SetSystemCursor(SDL_SystemCursor _cursor);

    int HideCursor();

    Vec2 GetCursorPos();
    Vec2 GetCursorWindowPos();


    typedef enum InitFlags
    {
        INIT_ANTIALIASING = 0x01,
        INIT_DISABLE_DEBUGGING = 0x02
    } InitFlags;

    // Initialize everything.
    int Init(std::string windowTitle, int _windowWidth, int _windowHeight, int initFlags);

    SDL_DisplayMode GetDisplayMode();

    int SetFullscreenResolution(int w, int h);

    GE_HWND GetHWND();

    void Mainloop();

}