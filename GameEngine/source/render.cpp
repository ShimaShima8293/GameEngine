#include "render.h"
#include "utilities.h"
#include "vars.h"
#include "audio.h"
#include "events.h"
#include "animation.h"
#include "resource.h"
#include "sprite/Renderable.h"

namespace GameEngine
{
    SDL_Texture* gamePlayTexture;
    SDL_Surface* surface;
    Timer renderTimer;
    Timer gameTimer;
    std::vector<Renderable*> mainLayer;
    std::vector<std::vector<Renderable*>*> layers = {};

    void RenderEverything()
    {
        float renderDuration = renderTimer.Get();
        renderTimer.Start();

        SDL_Rect destRect = {};

        double gameRatio = (double)GetGameWidth() / (double)GetGameHeight(); // Calculate the ratio of the game view
        double screenRatio = (double)GetWindowWidth() / (double)GetWindowHeight(); // Calculate the ratio of the window
        if (gameRatio == screenRatio)
        {
            destRect = { 0, 0, GetWindowWidth(), GetWindowHeight() };
        }
        else if (gameRatio > screenRatio)
        {
            destRect = { 0, (GetWindowHeight() - GetGameHeight() * GetWindowWidth() / GetGameWidth()) / 2, GetWindowWidth(), GetGameHeight() * GetWindowWidth() / GetGameWidth() };
        }
        else
        {
            destRect = { (GetWindowWidth() - GetGameWidth() * GetWindowHeight() / GetGameHeight()) / 2, 0, GetGameWidth() * GetWindowHeight() / GetGameHeight(), GetWindowHeight() };
        }


        SDL_DestroyTexture(gamePlayTexture);
        gamePlayTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, GetGameWidth(), GetGameHeight());
        SDL_SetTextureScaleMode(gamePlayTexture, SDL_ScaleModeBest);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderTarget(renderer, gamePlayTexture);


        int clipCount = 0;
        int renderedCount = 0;

        for (int i = 0; i < layers.size(); i++)
        {
            for (auto currentSprite = layers[i]->begin(); currentSprite != layers[i]->end();)
            {
                if ((*currentSprite) == nullptr)
                {
                    PrintErrorGE("RenderEverything: `currentSprite` was nullptr.");
                    currentSprite = layers[i]->erase(currentSprite);
                    continue;
                }
                (*currentSprite)->Render({});
                currentSprite++;
                //if (CheckCollision(currentSprite->GetRect(), { 0.0f, 0.0f, (float)GetGameWidth(), (float)GetGameHeight() }))
                //{
                //    currentSprite->Render();
                //    renderedCount++;
                //}
                //if (currentSprite->GetClip())
                //{
                //    clipCount++;
                //}
            }
        }

        for (auto currentSprite = mainLayer.begin(); currentSprite != mainLayer.end();)
        {
            if ((*currentSprite) == nullptr)
            {
                PrintErrorGE("RenderEverything: `currentSprite` was nullptr.");
                currentSprite = mainLayer.erase(currentSprite);
                continue;
            }
            (*currentSprite)->Render({});
            currentSprite++;
            //if (CheckCollision(currentSprite->GetRect(), { 0.0f, 0.0f, (float)GetGameWidth(), (float)GetGameHeight() }))
            //{
            //    currentSprite->Render();
            //    renderedCount++;
            //}
            //if (currentSprite->GetClip())
            //{
            //    clipCount++;
            //}
        }


        SDL_SetRenderTarget(renderer, NULL);
        SDL_RenderCopy(renderer, gamePlayTexture, NULL, &destRect);


        if (debug)
        {
            int fps = static_cast<int>(std::round(1.0f / renderDuration));

            std::string modeText = "Error";
            switch (GetWindowMode())
            {
            case WINDOW_FULLSCREEN:
                modeText = "Fullscreen";
                break;
            case WINDOW_FULLSCREEN_DESKTOP:
                modeText = "Fullscreen Desktop";
                break;
            case WINDOW_WINDOWED:
                modeText = "Windowed";
                break;
            default:
                modeText = "Unknown";
                break;
            }

            SDL_DisplayMode mode = GetDisplayMode();
            debugText.SetText(
                "Game Engine Version: " + std::string(GE_VERSION_STR) + "\n" +
                std::to_string(fps) + " fps\n"
                "Game resolution: " + std::to_string(GetGameWidth()) + "x" + std::to_string(GetGameHeight()) + "\n" +
                "Window resolution: " + std::to_string(GetWindowWidth()) + "x" + std::to_string(GetWindowHeight()) + "\n" +
                "Fullscreen resolution: " + std::to_string(mode.w) + "x" + std::to_string(mode.h) + "\n" +
                std::to_string(GetSpriteCount()) + " sprites (Clip: " + std::to_string(clipCount) + ", Rendered: " + std::to_string(renderedCount) + ")\n" +
                std::to_string(GetAnimationCount()) + " animations\n"
                "VSync: " + BoolToString(vsync) + "\n"
                "Anti-aliasing: " + BoolToString(antialiasing) + "\n"
                "Mute: " + BoolToString(GetMuteState()) + "\n"
                "Window mode: " + modeText + "\n"
                "Platform: " + SDL_GetPlatform() + "\n"
                "SDL version: " + std::to_string(SDL_MAJOR_VERSION) + "." + std::to_string(SDL_MINOR_VERSION) + "." + std::to_string(SDL_PATCHLEVEL) + "\n"
                "SDL_image version: " + std::to_string(SDL_IMAGE_MAJOR_VERSION) + "." + std::to_string(SDL_IMAGE_MINOR_VERSION) + "." + std::to_string(SDL_IMAGE_PATCHLEVEL) + "\n"
                "SDL_ttf version: " + std::to_string(SDL_TTF_MAJOR_VERSION) + "." + std::to_string(SDL_TTF_MINOR_VERSION) + "." + std::to_string(SDL_TTF_PATCHLEVEL) + "\n"
                "SDL_mixer version: " + std::to_string(SDL_MIXER_MAJOR_VERSION) + "." + std::to_string(SDL_MIXER_MINOR_VERSION) + "." + std::to_string(SDL_MIXER_PATCHLEVEL) + "\n"
                "Font: " + std::to_string(GetFontCount()) + "\n"
                "Music: " + std::to_string(GetMusicCount()) + "\n"
                "WAV: " + std::to_string(GetWAVCount()) + "\n"
                "Press F3 to hide"
            );
            debugBg.SetSize(debugText.GetW() + 10.0f, debugText.GetH() + 10.0f);
            debugBg.Render({});
            debugText.Render({});
        }

        SDL_RenderPresent(renderer);

        float gameDuration = gameTimer.Get();

        if (!vsync)
        {
            float ms = gameDuration * 1000.0f;
            float x;

            // 16 = ms + x
            // vvvvvvvvvvv
            // 16 - ms = x

            x = (1000.0f / 60.0f) - ms;

            if (x > 0)
            {
                SDL_Delay((Uint32)x);
            }
        }

        gameTimer.Start();
    }

    void AddSprite(Renderable* sprite)
    {
        if (sprite == nullptr)
        {
            PrintErrorGE("AddSprite: Parameter `sprite` was nullptr.");
            return;
        }
        mainLayer.push_back(sprite);
    }

    void SetLayers(std::vector<std::vector<Renderable*>*> _layers)
    {
        layers = _layers;
    }

    int GetSpriteCount()
    {
        int size = (int)mainLayer.size();

        for (int i = 0; i < layers.size(); i++)
        {
            size += (int)layers[i]->size();
        }
        return size;
    }

    void RemoveSprite(Renderable* sprite)
    {
        if (sprite == nullptr)
        {
            PrintErrorGE("RemoveSprite: Parameter `sprite` was nullptr.");
            return;
        }
        for (auto currentSprite = mainLayer.begin(); currentSprite != mainLayer.end();)
        {
            if ((*currentSprite) == sprite)
            {
                currentSprite = mainLayer.erase(currentSprite);
                continue;
            }
            currentSprite++;
        }
        for (int i = 0; i < layers.size(); i++)
        {
            for (auto currentSprite = layers[i]->begin(); currentSprite != layers[i]->end();)
            {
                if ((*currentSprite) == sprite)
                {
                    currentSprite = layers[i]->erase(currentSprite);
                    continue;
                }
                currentSprite++;
            }
        }
    }

    void ClearSprites()
    {
        for (int i = 0; i < layers.size(); i++)
        {
            layers[i]->clear();
        }

        layers.clear();
        mainLayer.clear();
    }

}