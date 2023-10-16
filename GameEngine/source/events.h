#pragma once

#include "internal.h"

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
void processEvents();

// Get if the window is focused.
// \returns bool True if the window is focused; False if not.
bool getWindowFocus();

// Get if a key is pressed.
// \param code The key code from SDL_KeyCode.
// \returns bool True if the requested key is pressed down.
bool getKeyPressed(SDL_KeyCode code);

// Get if a key is pressed. It is similar to `getKeyPressed()` but this function will only return true when the requested key got pressed on current frame.
// \param code The key code from SDL_KeyCode.
// \returns bool True if the requested key is pressed down on current frame.
bool getKeyPressedPulse(SDL_KeyCode code);

// Get if a joycon button is pressed.
// \param button The index of the button.
// \returns bool True if the requested button is pressed down.
bool getJoyButton(int button);

// Get if a joycon button is pressed.
// \param button The index of the button.
// \returns bool True if the requested button is pressed down.
bool getJoyButtonPulse(int button);
int getJoyAxis(int axis);
bool getJoyAxisPulse(int axis, AxisDirection direction, int deadzone);
bool getRunning();
void endMainloop();
// Frees things and quits SDL.
void close();
int getGameWidth();
int getGameHeight();
SDL_Window* getWindow();
SDL_Renderer* getRenderer();
int getWindowWidth();
int getWindowHeight();
void setWindowMode(WindowMode mode);
WindowMode getWindowMode();
int setSystemCursor(SDL_SystemCursor _cursor);
int hideCursor();

typedef enum InitFlags
{
    INIT_ANTIALIASING = 0x01,
    INIT_DISABLE_DEBUGGING = 0x02
} InitFlags;

// Initialize everything.
int init(std::string windowTitle, int _windowWidth, int _windowHeight, int initFlags);

SDL_DisplayMode getDisplayMode();

int setFullscreenResolution(int w, int h);

void startMainloop();
