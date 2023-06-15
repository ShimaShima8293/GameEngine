#include "resource.h"

namespace GameEngine
{
    std::vector<TTF_Font*> fontList = {};
    std::vector<Mix_Music*> musicList = {};
    std::vector<Mix_Chunk*> chunkList = {};
}
using namespace GameEngine;

TTF_Font* openFont(std::string path, int size)
{
    TTF_Font* _font = TTF_OpenFont(path.c_str(), size);
    if (_font == NULL)
    {
        printError("Could not open a font... SDL_TTF Error: " << TTF_GetError());
    }
    else
    {
        fontList.push_back(_font);
    }
    return _font;
}
Mix_Music* openMusic(std::string path)
{
    Mix_Music* _music = Mix_LoadMUS(path.c_str());
    if (_music == NULL)
    {
        printError("Could not open an audio... SDL_MIX Error: " << Mix_GetError());
    }
    else
    {
        musicList.push_back(_music);
    }
    return _music;
}
Mix_Chunk* openWAV(std::string path)
{
    Mix_Chunk* _chunk = Mix_LoadWAV(path.c_str());
    if (_chunk == NULL)
    {
        printError("Could not open an WAV chunk... SDL_MIX Error: " << Mix_GetError());
    }
    else
    {
        chunkList.push_back(_chunk);
    }
    return _chunk;
}

void closeResources()
{
    for (int i = 0; i < fontList.size(); i++)
    {
        TTF_CloseFont(fontList[i]);
        printInfo("Closed a font");
    }
    for (int i = 0; i < musicList.size(); i++)
    {
        Mix_FreeMusic(musicList[i]);
        printInfo("Closed a music");
    }
    for (int i = 0; i < chunkList.size(); i++)
    {
        Mix_FreeChunk(chunkList[i]);
        printInfo("Closed a WAV chunk");
    }
}