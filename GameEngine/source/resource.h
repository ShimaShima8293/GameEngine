#pragma once
#include "internal.h"

namespace GameEngine
{
    // Open a font. It will Print out an error message if it failed to load. Don't forget to release the memory with `CloseResources()` or `CloseFont()`!
    // \param _font The loaded font to check.
    // \returns Returns a pointer to TTF_Font, which is required for `Sprite::loadFromText()`.
    TTF_Font* OpenFont(std::string path, int size);

    // Open an audio file. It will Print out an error message if it failed to load. Don't forget to release the memory with `CloseResources()` or `CloseMusic()`!
    // \param _music The loaded music to check.
    // \returns Returns a pointer to Mix_Music.
    Mix_Music* OpenMusic(std::string path);

    // Open a wave file. It will Print out an error message if it failed to load. Don't forget to release the memory with `CloseResources()` or `CloseWAV()`!
    // \param _chunk The loaded chunk to check.
    // \returns Returns a pointer to Mix_Chunk, which is required for `PlayMusicSet()`
    Mix_Chunk* OpenWAV(std::string path);

    SDL_Texture* CreateFromImage(std::string path);

    void CloseFont(TTF_Font*& font);

    void CloseMusic(Mix_Music*& music);

    void CloseWAV(Mix_Chunk*& chunk);

    // Close all the resources opened by `OpenFont()`, `OpenMusic()`, and `OpenWAV`. Call this function after finishing the main loop.
    void CloseResources();

    int GetFontCount();

    int GetMusicCount();

    int GetWAVCount();

}