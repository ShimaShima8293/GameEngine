#pragma once

#include "macros.h"
#include PATH_SDL
#include <string>

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

// Initialize everything.
void init(std::string windowTitle, int _windowWidth, int _windowHeight, int _windowFlags, bool _debug, bool renderQuality);
