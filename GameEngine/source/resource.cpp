#include "resource.h"
#include "events.h"

namespace GameEngine
{
    std::vector<TTF_Font*> fontList = {};
    std::vector<Mix_Music*> musicList = {};
    std::vector<Mix_Chunk*> chunkList = {};

    TTF_Font* openFont(std::string path, int size)
    {
        TTF_Font* _font = TTF_OpenFont(path.c_str(), size);
        if (_font == NULL)
        {
            printError("openFont: Failed to open a font.");
            printSDLError();
            return nullptr;
        }

        fontList.push_back(_font);
        printInfo("openFont: Opened a font at " + path);
        return _font;
    }
    Mix_Music* openMusic(std::string path)
    {
        Mix_Music* _music = Mix_LoadMUS(path.c_str());
        if (_music == NULL)
        {
            printError("openMusic: Failed to open a music.");
            printSDLError();
            return nullptr;
        }

        musicList.push_back(_music);
        printInfo("openMusic: Opened a music at " + path);
        return _music;
    }
    Mix_Chunk* openWAV(std::string path)
    {
        Mix_Chunk* _chunk = Mix_LoadWAV(path.c_str());
        if (_chunk == NULL)
        {
            printError("openWAV: Failed to open a WAV chunk.");
            printSDLError();
            return nullptr;
        }

        chunkList.push_back(_chunk);
        printInfo("openWAV: Opened a WAV chunk at " + path);
        return _chunk;
    }

    SDL_Texture* createFromImage(std::string path)
    {
        SDL_Texture* texture = nullptr;
        texture = IMG_LoadTexture(getRenderer(), path.c_str());
        if (texture == nullptr)
        {
            printError("createFromImage: Failed to create image texture.");
            printSDLError();
        }

        return texture;
    }

    void closeFont(TTF_Font*& font)
    {
        if (font == nullptr)
        {
            printError("closeFont: Parameter `font` was nullptr.");
            return;
        }
        for (int i = 0; i < fontList.size(); i++)
        {
            if (font == fontList[i])
            {
                TTF_CloseFont(fontList[i]);
                fontList.erase(fontList.begin() + i);
                i--;
                printInfo("closeFont: Closed a font");
            }
        }
        font = nullptr;
    }

    void closeMusic(Mix_Music*& music)
    {
        if (music == nullptr)
        {
            printError("closeMusic: Parameter `music` was nullptr.");
            return;
        }
        for (int i = 0; i < musicList.size(); i++)
        {
            if (music == musicList[i])
            {
                Mix_FreeMusic(musicList[i]);
                musicList.erase(musicList.begin() + i);
                i--;
                printInfo("closeMusic: Closed a music");
            }
        }
        music = nullptr;
    }

    void closeWAV(Mix_Chunk*& chunk)
    {
        if (chunk == nullptr)
        {
            printError("closeWAV: Parameter `chunk` was nullptr.");
            return;
        }
        for (int i = 0; i < chunkList.size(); i++)
        {
            if (chunk == chunkList[i])
            {
                Mix_FreeChunk(chunkList[i]);
                chunkList.erase(chunkList.begin() + i);
                i--;
                printInfo("closeWAV: Closed a WAV chunk");
            }
        }
        chunk = nullptr;
    }


    void closeResources()
    {
        for (int i = 0; i < fontList.size(); i++)
        {
            TTF_CloseFont(fontList[i]);
            printInfo("closeResources: Closed a font");
        }
        fontList.clear();
        for (int i = 0; i < musicList.size(); i++)
        {
            Mix_FreeMusic(musicList[i]);
            printInfo("closeResources: Closed a music");
        }
        musicList.clear();
        for (int i = 0; i < chunkList.size(); i++)
        {
            Mix_FreeChunk(chunkList[i]);
            printInfo("closeResources: Closed a WAV chunk");
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

}