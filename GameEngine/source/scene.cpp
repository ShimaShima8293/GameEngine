#include <iostream>
#include "macros.h"
#include "scene.h"
#include <vector>
#include "events.h"
#include "render.h"
#include "update.h"

namespace GameEngine
{
    Scene* queue;
    Scene* current;
}

using namespace GameEngine;

void loadScene(Scene* scene)
{
    queue = scene;
}

void processScene()
{
    if (queue != nullptr)
    {
        if (current != nullptr)
        {
            current->free();
        }

        initScene();
        printInfo("processScene: loading a scene (" << queue << ")");
        queue->start();
        current = queue;
        queue = nullptr;
    }

    if (getCurrentScene() != nullptr)
    {
        getCurrentScene()->update();
    }
}

void initScene()
{
    clearEntities();
    clearUpdates();
}

Scene* getCurrentScene()
{
    return current;
}

void reloadCurrentScene()
{
    loadScene(current);
}