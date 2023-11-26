#include "render.h"
#include "utilities.h"
#include "vars.h"
#include "audio.h"
#include "events.h"
#include "animation.h"
#include "resource.h"

namespace GameEngine
{
    SDL_Texture* gamePlayTexture;
    SDL_Surface* surface;
    Timer renderTimer;
    Timer gameTimer;
    std::vector<Renderable*> mainLayer;
    std::vector<std::vector<Renderable*>*> layers = {};

    void renderEverything()
    {
        float renderDuration = renderTimer.get();
        renderTimer.start();

        SDL_Rect destRect = {};

        double gameRatio = (double)getGameWidth() / (double)getGameHeight(); // Calculate the ratio of the game view
        double screenRatio = (double)getWindowWidth() / (double)getWindowHeight(); // Calculate the ratio of the window
        if (gameRatio == screenRatio)
        {
            destRect = { 0, 0, getWindowWidth(), getWindowHeight() };
        }
        else if (gameRatio > screenRatio)
        {
            destRect = { 0, (getWindowHeight() - getGameHeight() * getWindowWidth() / getGameWidth()) / 2, getWindowWidth(), getGameHeight() * getWindowWidth() / getGameWidth() };
        }
        else
        {
            destRect = { (getWindowWidth() - getGameWidth() * getWindowHeight() / getGameHeight()) / 2, 0, getGameWidth() * getWindowHeight() / getGameHeight(), getWindowHeight() };
        }


        SDL_DestroyTexture(gamePlayTexture);
        gamePlayTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, getGameWidth(), getGameHeight());
        SDL_SetTextureScaleMode(gamePlayTexture, SDL_ScaleModeBest);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderTarget(renderer, gamePlayTexture);


        int clipCount = 0;
        int renderedCount = 0;

        for (int i = 0; i < layers.size(); i++)
        {
            for (int j = 0; j < layers[i]->size(); j++)
            {
                Renderable* currentSprite = (*layers[i])[j];
                if (currentSprite == nullptr)
                {
                    printErrorGE("renderEverything: `currentSprite` was nullptr.");
                    continue;
                }
                currentSprite->render({});
                //if (checkCollision(currentSprite->getRect(), { 0.0f, 0.0f, (float)getGameWidth(), (float)getGameHeight() }))
                //{
                //    currentSprite->render();
                //    renderedCount++;
                //}
                //if (currentSprite->getClip())
                //{
                //    clipCount++;
                //}
            }
        }

        for (int i = 0; i < mainLayer.size(); i++)
        {
            Renderable* currentSprite = mainLayer[i];
            if (currentSprite == nullptr)
            {
                printErrorGE("renderEverything: `currentSprite` was nullptr.");
                continue;
            }
            currentSprite->render({});
            //if (checkCollision(currentSprite->getRect(), { 0.0f, 0.0f, (float)getGameWidth(), (float)getGameHeight() }))
            //{
            //    currentSprite->render();
            //    renderedCount++;
            //}
            //if (currentSprite->getClip())
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
            switch (getWindowMode())
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

            SDL_DisplayMode mode = getDisplayMode();
            debugText.setText(
                "Game Engine Version: " + std::string(GE_VERSION_STR) + "\n" +
                std::to_string(fps) + " fps\n"
                "Game resolution: " + std::to_string(getGameWidth()) + "x" + std::to_string(getGameHeight()) + "\n" +
                "Window resolution: " + std::to_string(getWindowWidth()) + "x" + std::to_string(getWindowHeight()) + "\n" +
                "Fullscreen resolution: " + std::to_string(mode.w) + "x" + std::to_string(mode.h) + "\n" +
                std::to_string(getSpriteCount()) + " sprites (Clip: " + std::to_string(clipCount) + ", Rendered: " + std::to_string(renderedCount) + ")\n" +
                std::to_string(getAnimationCount()) + " animations\n"
                "VSync: " + bool2string(vsync) + "\n"
                "Anti-aliasing: " + bool2string(antialiasing) + "\n"
                "Mute: " + bool2string(getMuteState()) + "\n"
                "Window mode: " + modeText + "\n"
                "Platform: " + SDL_GetPlatform() + "\n"
                "SDL version: " + std::to_string(SDL_MAJOR_VERSION) + "." + std::to_string(SDL_MINOR_VERSION) + "." + std::to_string(SDL_PATCHLEVEL) + "\n"
                "SDL_image version: " + std::to_string(SDL_IMAGE_MAJOR_VERSION) + "." + std::to_string(SDL_IMAGE_MINOR_VERSION) + "." + std::to_string(SDL_IMAGE_PATCHLEVEL) + "\n"
                "SDL_ttf version: " + std::to_string(SDL_TTF_MAJOR_VERSION) + "." + std::to_string(SDL_TTF_MINOR_VERSION) + "." + std::to_string(SDL_TTF_PATCHLEVEL) + "\n"
                "SDL_mixer version: " + std::to_string(SDL_MIXER_MAJOR_VERSION) + "." + std::to_string(SDL_MIXER_MINOR_VERSION) + "." + std::to_string(SDL_MIXER_PATCHLEVEL) + "\n"
                "Font: " + std::to_string(getFontCount()) + "\n"
                "Music: " + std::to_string(getMusicCount()) + "\n"
                "WAV: " + std::to_string(getWAVCount()) + "\n"
                "Press F3 to hide"
            );
            debugBg.setSize(debugText.getW() + 10.0f, debugText.getH() + 10.0f);
            debugBg.render({});
            debugText.render({});
        }

        SDL_RenderPresent(renderer);

        float gameDuration = gameTimer.get();

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

        gameTimer.start();
    }

    void addSprite(Renderable* sprite)
    {
        if (sprite == nullptr)
        {
            printErrorGE("addSprite: Parameter `sprite` was nullptr.");
            return;
        }
        mainLayer.push_back(sprite);
    }

    void setLayers(std::vector<std::vector<Renderable*>*> _layers)
    {
        layers = _layers;
    }

    int getSpriteCount()
    {
        int size = (int)mainLayer.size();

        for (int i = 0; i < layers.size(); i++)
        {
            size += (int)layers[i]->size();
        }
        return size;
    }

    void removeSprite(Renderable* sprite)
    {
        if (sprite == nullptr)
        {
            printErrorGE("removeSprite: Parameter `sprite` was nullptr.");
            return;
        }
        for (int i = 0; i < mainLayer.size(); i++)
        {
            if (mainLayer[i] == sprite)
            {
                mainLayer.erase(mainLayer.begin() + i);
                i--;
            }
        }
        for (int i = 0; i < layers.size(); i++)
        {
            for (int j = 0; j < layers[i]->size(); j++)
            {
                if ((*layers[i])[j] == sprite)
                {
                    layers[i]->erase(layers[i]->begin() + j);
                    j--;
                }
            }
        }
    }

    void clearSprites()
    {
        for (int i = 0; i < layers.size(); i++)
        {
            layers[i]->clear();
        }

        layers.clear();
        mainLayer.clear();
    }

}