#include <iostream>
#include <string>
#include "render.h"
#include "utilities.h"
#include "macros.h"
#include "Timer.h"
#include "vars.h"
#include "audio.h"
#include "events.h"
#include "update.h"

namespace GameEngine
{
    SDL_Texture* gamePlayTexture;
    SDL_Surface* surface;
    Timer renderTimer;
    Timer gameTimer;
    std::vector<Entity*> mainLayer;
}
using namespace GameEngine;

void renderEverything()
{
    float renderDuration = renderTimer.get();
    renderTimer.start();

    SDL_Rect destRect = {};

    double gameRatio = (double)getGameWidth() / (double)getGameHeight(); // Calculate the ratio of the game view
    double screenRatio = (double)windowWidth / (double)windowHeight; // Calculate the ratio of the window
    if (gameRatio == screenRatio)
    {
        destRect = { 0, 0, windowWidth, windowHeight };
    }
    else if (gameRatio > screenRatio)
    {
        destRect = { 0, (windowHeight - getGameHeight() * windowWidth / getGameWidth()) / 2, windowWidth, getGameHeight() * windowWidth / getGameWidth() };
    }
    else
    {
        destRect = { (windowWidth - getGameWidth() * windowHeight / getGameHeight()) / 2, 0, getGameWidth() * windowHeight / getGameHeight(), windowHeight };
    }


    SDL_DestroyTexture(gamePlayTexture);
    gamePlayTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, getGameWidth(), getGameHeight());

    SDL_RenderClear(renderer);
    SDL_SetRenderTarget(renderer, gamePlayTexture);



    int entityCount = 0;
    int clipCount = 0;
    Entity* currentEntity;
    for (int i = 0; i < mainLayer.size(); i++)
    {
        currentEntity = mainLayer[i];
        currentEntity->render();
        if (currentEntity->getClip())
        {
            clipCount++;
        }
        entityCount++;

    }


    SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderCopy(renderer, gamePlayTexture, NULL, &destRect);


    if (debug)
    {
        int fps = static_cast<int>(std::round(1.0f / renderDuration));

        std::string debugStr =
            std::to_string(fps) + " fps\n" +
            std::to_string(entityCount) + " entities (Clip: " + std::to_string(clipCount) + ")\n" +
            std::to_string(getUpdateCount()) + " updates\n"
            "VSync: " + bool2string(vsync) + "\n"
            "Mute: " + bool2string(getMuteState()) + "\n"
            "Window mode: " + windowMode + "\n"
            "Anti-aliasing: " + bool2string(antialiasing) + "\n"
            "Press F3 to hide";

        debugText.setText(debugStr);

        debugText.render();
    }

    SDL_RenderPresent(renderer);

    float gameDuration = gameTimer.get();

    if (!vsync)
    {
        float ms = gameDuration * 1000.0f;
        float x = 0.0f;

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
    mainLayer.push_back(entity);
}

int getEntityCount()
{
    return mainLayer.size();
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

int removeEntity(int index)
{
    if (index <= getEntityCount())
    {
        mainLayer.erase(mainLayer.begin() + index);
        return 0;
    }
    else
    {
        printError("removeEntity: index is too large");
        return -1;
    }
}

void clearEntities()
{
    mainLayer.clear();
}