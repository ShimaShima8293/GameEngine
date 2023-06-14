#pragma once
#include "macros.h"
#include PATH_SDL
#include PATH_SDL_TTF
#include PATH_SDL_MIXER
#include <string>
#include <vector>

// Open a font. It will Print out an error message if it failed to load.
// \param _font The loaded font to check.
// \returns Returns a pointer to TTF_Font, which is required for `Entity::loadFromText()`.
TTF_Font* openFont(std::string path, int size);

// Open an audio file. It will Print out an error message if it failed to load.
// \param _music The loaded music to check.
// \returns Returns a pointer to Mix_Music.
Mix_Music* openMusic(std::string path);

// Open a wave file. It will Print out an error message if it failed to load.
// \param _chunk The loaded chunk to check.
// \returns Returns a pointer to Mix_Chunk, which is required for `playMusicSet()`
Mix_Chunk* openWAV(std::string path);

// Close all the resources opened by `openFont()`, `openMusic()`, and `openWAV`. Call this function after finishing the main loop.
void closeResources();