#pragma once
#include "internal.h"

namespace GameEngine
{
    // Open a font. It will Print out an error message if it failed to load. Don't forget to release the memory with `closeResources()` or `closeFont()`!
    // \param _font The loaded font to check.
    // \returns Returns a pointer to TTF_Font, which is required for `Sprite::loadFromText()`.
    TTF_Font* openFont(std::string path, int size);

    // Open an audio file. It will Print out an error message if it failed to load. Don't forget to release the memory with `closeResources()` or `closeMusic()`!
    // \param _music The loaded music to check.
    // \returns Returns a pointer to Mix_Music.
    Mix_Music* openMusic(std::string path);

    // Open a wave file. It will Print out an error message if it failed to load. Don't forget to release the memory with `closeResources()` or `closeWAV()`!
    // \param _chunk The loaded chunk to check.
    // \returns Returns a pointer to Mix_Chunk, which is required for `playMusicSet()`
    Mix_Chunk* openWAV(std::string path);

    SDL_Texture* createFromImage(std::string path);

    void closeFont(TTF_Font*& font);

    void closeMusic(Mix_Music*& music);

    void closeWAV(Mix_Chunk*& chunk);

    // Close all the resources opened by `openFont()`, `openMusic()`, and `openWAV`. Call this function after finishing the main loop.
    void closeResources();

    int getFontCount();

    int getMusicCount();

    int getWAVCount();

}