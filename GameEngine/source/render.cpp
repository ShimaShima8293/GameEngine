#include <iostream>
#include <string>
#include <cmath>
#include "render.h"
#include "utilities.h"
#include "macros.h"
#include "Timer.h"
#include "vars.h"
#include "audio.h"
#include "events.h"
#include "update.h"
#include "animation.h"
#include "resource.h"

namespace GameEngine
{
    SDL_Texture* gamePlayTexture;
    SDL_Surface* surface;
    Timer renderTimer;
    Timer gameTimer;
    std::vector<Entity*> mainLayer;
    std::vector<std::vector<Entity*>*> layers = {};
}
using namespace GameEngine;

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
    Entity* currentEntity;

    for (int i = 0; i < layers.size(); i++)
    {
        for (int j = 0; j < layers[i]->size(); j++)
        {
            currentEntity = (*layers[i])[j];
            if (currentEntity == nullptr)
            {
                printError("renderEverything: currentEntity was nullptr.");
                continue;
            }
            currentEntity->render();
            if (currentEntity->getClip())
            {
                clipCount++;
            }
        }
    }

    for (int i = 0; i < mainLayer.size(); i++)
    {
        currentEntity = mainLayer[i];
        if (currentEntity == nullptr)
        {
            printError("renderEverything: currentEntity was nullptr.");
            continue;
        }
        currentEntity->render();
        if (currentEntity->getClip())
        {
            clipCount++;
        }
    }


    SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderCopy(renderer, gamePlayTexture, NULL, &destRect);


    if (debug)
    {
        int fps = static_cast<int>(std::round(1.0f / renderDuration));

        std::string modeText = "Unknown";
        if (getWindowMode() == WINDOW_FULLSCREEN)
        {
            modeText = "Fullscreen";
        }
        else if (getWindowMode() == WINDOW_FULLSCREEN_DESKTOP)
        {
            modeText = "Fullscreen Desktop";
        }
        else if (getWindowMode() == WINDOW_WINDOWED)
        {
            modeText = "Windowed";
        }
        SDL_DisplayMode mode = getDisplayMode();
        debugText.setText(
            "Game Engine Version: " + std::string(GE_VERSION_STR) + "\n" +
            std::to_string(fps) + " fps\n"
            "Game resolution: " + std::to_string(getGameWidth()) + "x" + std::to_string(getGameHeight()) + "\n" +
            "Window resolution: " + std::to_string(getWindowWidth()) + "x" + std::to_string(getWindowHeight()) + "\n" +
            "Fullscreen resolution: " + std::to_string(mode.w) + "x" + std::to_string(mode.h) + "\n" +
            std::to_string(getEntityCount()) + " entities (Clip: " + std::to_string(clipCount) + ")\n" +
            std::to_string(getUpdateCount()) + " updates\n" +
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
        debugBg.render();
        debugText.render();
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

void addEntity(Entity* entity)
{
    if (entity == nullptr)
    {
        printError("addEntity: parameter entity was nullptr.");
        return;
    }
    mainLayer.push_back(entity);
}

void setLayers(std::vector<std::vector<Entity*>*> _layers)
{
    layers = _layers;
}

int getEntityCount()
{
    int size = (int)mainLayer.size();

    for (int i = 0; i < layers.size(); i++)
    {
        size += (int)layers[i]->size();
    }
    return size;
}

Entity* getEntity(int index)
{
    if (index <= getEntityCount())
    {
        return mainLayer[index];
    }
    else
    {
        printError("getEntity: index is too large");
        return nullptr;
    }
}

void removeEntity(Entity* entity)
{
    for (int i = 0; i < mainLayer.size(); i++)
    {
        if (mainLayer[i] == entity)
        {
            mainLayer.erase(mainLayer.begin() + i);
        }
    }
    for (int i = 0; i < layers.size(); i++)
    {
        for (int j = 0; j < layers[i]->size(); j++)
        {
            if ((*layers[i])[j] == entity)
            {
                layers[i]->erase(layers[i]->begin() + j);
            }
        }
    }
}

void clearEntities()
{
    for (int i = 0; i < layers.size(); i++)
    {
        layers[i]->clear();
    }

    layers.clear();
    mainLayer.clear();
}
