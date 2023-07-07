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

// Processes events. Updates `KeyPressed` and `KeyPressedPulse`.
void processEvents();
bool getWindowFocus();
bool getKeyPressed(SDL_KeyCode code);
bool getKeyPressedPulse(SDL_KeyCode code);
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
void setSystemCursor(SDL_SystemCursor _cursor);
void hideCursor();

// Initialize everything.
void init(std::string windowTitle, int _windowWidth, int _windowHeight, int _windowFlags, bool _debug, bool renderQuality);

SDL_DisplayMode getDisplayMode();
