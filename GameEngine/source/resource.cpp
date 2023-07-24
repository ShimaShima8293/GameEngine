#include "resource.h"
#include "events.h"

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
        printError("openFont: Could not open a font... SDL_TTF Error: " << TTF_GetError());
        return nullptr;
    }

    fontList.push_back(_font);
    printInfo("openFont: opened a font at " << path << " (" << _font << ")");
    return _font;
}
Mix_Music* openMusic(std::string path)
{
    Mix_Music* _music = Mix_LoadMUS(path.c_str());
    if (_music == NULL)
    {
        printError("openMusic: Could not open an audio... SDL_MIX Error: " << Mix_GetError());
        return nullptr;
    }

    musicList.push_back(_music);
    printInfo("openMusic: opened a music at " << path << " (" << _music << ")");
    return _music;
}
Mix_Chunk* openWAV(std::string path)
{
    Mix_Chunk* _chunk = Mix_LoadWAV(path.c_str());
    if (_chunk == NULL)
    {
        printError("openWAV: Could not open an WAV chunk... SDL_MIX Error: " << Mix_GetError());
        return nullptr;
    }

    chunkList.push_back(_chunk);
    printInfo("openWAV: opened a WAV chunk at " << path << " (" << _chunk << ")");
    return _chunk;
}

SDL_Texture* createFromImage(std::string path)
{
    SDL_Texture* texture = nullptr;
    texture = IMG_LoadTexture(getRenderer(), path.c_str());
    if (texture == nullptr)
    {
        printError("createFromImage: Failed to create image texture. SDL Error: " << SDL_GetError());
    }

    return texture;
}

void closeFont(TTF_Font* font)
{
    if (font == nullptr)
    {
        printError("closeFont: nullptr passed");
        return;
    }
    for (int i = 0; i < fontList.size(); i++)
    {
        if (font == fontList[i])
        {
            TTF_CloseFont(fontList[i]);
            fontList.erase(fontList.begin() + i);
            i--;
            printInfo("closeFont: Closed a font (" << font << ")");
        }
    }
    font = nullptr;
}

void closeMusic(Mix_Music* music)
{
    if (music == nullptr)
    {
        printError("closeMusic: nullptr passed");
        return;
    }
    for (int i = 0; i < musicList.size(); i++)
    {
        if (music == musicList[i])
        {
            Mix_FreeMusic(musicList[i]);
            musicList.erase(musicList.begin() + i);
            i--;
            printInfo("closeMusic: Closed a music (" << music << ")");
        }
    }
    music = nullptr;
}

void closeWAV(Mix_Chunk* chunk)
{
    if (chunk == nullptr)
    {
        printError("closeWAV: nullptr passed");
        return;
    }
    for (int i = 0; i < chunkList.size(); i++)
    {
        if (chunk == chunkList[i])
        {
            Mix_FreeChunk(chunkList[i]);
            chunkList.erase(chunkList.begin() + i);
            i--;
            printInfo("closeWAV: Closed a WAV chunk (" << chunk << ")");
        }
    }
    chunk = nullptr;
}


void closeResources()
{
    for (int i = 0; i < fontList.size(); i++)
    {
        TTF_CloseFont(fontList[i]);
        printInfo("closeResources: Closed a font (" << fontList[i] << ")");
    }
    fontList.clear();
    for (int i = 0; i < musicList.size(); i++)
    {
        Mix_FreeMusic(musicList[i]);
        printInfo("closeResources: Closed a music (" << musicList[i] << ")");
    }
    musicList.clear();
    for (int i = 0; i < chunkList.size(); i++)
    {
        Mix_FreeChunk(chunkList[i]);
        printInfo("closeResources: Closed a WAV chunk (" << chunkList[i] << ")");
    }
    chunkList.clear();
}

int getFontCount()
{
    return (int)fontList.size();
}

int getMusicCount()
{
    return (int)musicList.size();
}

int getWAVCount()
{
    return (int)chunkList.size();
}