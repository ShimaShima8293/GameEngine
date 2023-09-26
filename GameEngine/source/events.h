#pragma once

#include "macros.h"
#include PATH_SDL
#include <string>

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
bool getWindowFocus();
bool getKeyPressed(SDL_KeyCode code);
bool getKeyPressedPulse(SDL_KeyCode code);
bool getJoyButton(int button);
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
