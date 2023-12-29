#include "resource.h"
#include "events.h"

namespace GameEngine
{
    std::vector<TTF_Font*> fontList = {};
    std::vector<Mix_Music*> musicList = {};
    std::vector<Mix_Chunk*> chunkList = {};

    TTF_Font* OpenFont(std::string path, int size)
    {
        TTF_Font* _font = TTF_OpenFont(path.c_str(), size);
        if (_font == NULL)
        {
            PrintErrorGE("OpenFont: Failed to open a font.");
            PrintSDLError();
            return nullptr;
        }

        fontList.push_back(_font);
        PrintInfoGE("OpenFont: Opened a font at " + path);
        return _font;
    }
    Mix_Music* OpenMusic(std::string path)
    {
        Mix_Music* _music = Mix_LoadMUS(path.c_str());
        if (_music == NULL)
        {
            PrintErrorGE("OpenMusic: Failed to open a music.");
            PrintSDLError();
            return nullptr;
        }

        musicList.push_back(_music);
        PrintInfoGE("OpenMusic: Opened a music at " + path);
        return _music;
    }
    Mix_Chunk* OpenWAV(std::string path)
    {
        Mix_Chunk* _chunk = Mix_LoadWAV(path.c_str());
        if (_chunk == NULL)
        {
            PrintErrorGE("OpenWAV: Failed to open a WAV chunk.");
            PrintSDLError();
            return nullptr;
        }

        chunkList.push_back(_chunk);
        PrintInfoGE("OpenWAV: Opened a WAV chunk at " + path);
        return _chunk;
    }

    SDL_Texture* CreateFromImage(std::string path)
    {
        SDL_Texture* texture = nullptr;
        texture = IMG_LoadTexture(GetRenderer(), path.c_str());
        if (texture == nullptr)
        {
            PrintErrorGE("CreateFromImage: Failed to create image texture.");
            PrintSDLError();
        }

        return texture;
    }

    void CloseFont(TTF_Font*& font)
    {
        if (font == nullptr)
        {
            PrintErrorGE("CloseFont: Parameter `font` was nullptr.");
            return;
        }
        for (int i = 0; i < fontList.size(); i++)
        {
            if (font == fontList[i])
            {
                TTF_CloseFont(fontList[i]);
                fontList.erase(fontList.begin() + i);
                i--;
                PrintInfoGE("CloseFont: Closed a font");
            }
        }
        font = nullptr;
    }

    void CloseMusic(Mix_Music*& music)
    {
        if (music == nullptr)
        {
            PrintErrorGE("CloseMusic: Parameter `music` was nullptr.");
            return;
        }
        for (int i = 0; i < musicList.size(); i++)
        {
            if (music == musicList[i])
            {
                Mix_FreeMusic(musicList[i]);
                musicList.erase(musicList.begin() + i);
                i--;
                PrintInfoGE("CloseMusic: Closed a music");
            }
        }
        music = nullptr;
    }

    void CloseWAV(Mix_Chunk*& chunk)
    {
        if (chunk == nullptr)
        {
            PrintErrorGE("CloseWAV: Parameter `chunk` was nullptr.");
            return;
        }
        for (int i = 0; i < chunkList.size(); i++)
        {
            if (chunk == chunkList[i])
            {
                Mix_FreeChunk(chunkList[i]);
                chunkList.erase(chunkList.begin() + i);
                i--;
                PrintInfoGE("CloseWAV: Closed a WAV chunk");
            }
        }
        chunk = nullptr;
    }


    void CloseResources()
    {
        for (int i = 0; i < fontList.size(); i++)
        {
            TTF_CloseFont(fontList[i]);
            PrintInfoGE("CloseResources: Closed a font");
        }
        fontList.clear();
        for (int i = 0; i < musicList.size(); i++)
        {
            Mix_FreeMusic(musicList[i]);
            PrintInfoGE("CloseResources: Closed a music");
        }
        musicList.clear();
        for (int i = 0; i < chunkList.size(); i++)
        {
            Mix_FreeChunk(chunkList[i]);
            PrintInfoGE("CloseResources: Closed a WAV chunk");
        }
        chunkList.clear();
    }

    int GetFontCount()
    {
        return (int)fontList.size();
    }

    int GetMusicCount()
    {
        return (int)musicList.size();
    }

    int GetWAVCount()
    {
        return (int)chunkList.size();
    }

}