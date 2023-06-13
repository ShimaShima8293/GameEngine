#pragma once
#include "macros.h"
#include PATH_SDL
#include PATH_SDL_TTF
#include PATH_SDL_MIXER
#include <string>
#include <vector>

// Checks if the loaded font is null or not. It will Print out an error message if it failed to load.
// \param _font The loaded font to check.
TTF_Font* openFont(std::string path, int size);
// Checks if the loaded music is null or not. It will Print out an error message if it failed to load.
// \param _music The loaded music to check.
Mix_Music* openMusic(std::string path);
// Checks if the loaded chunk is null or not. It will Print out an error message if it failed to load.
// \param _chunk The loaded chunk to check.
Mix_Chunk* openWAV(std::string path);
void closeResources();