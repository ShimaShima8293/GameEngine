#include <iostream>
#include "macros.h"
#include "scene.h"
#include <vector>
#include "events.h"
#include "render.h"
#include "animation.h"

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
        current = queue;
        queue->start();
        if (current == queue)
        {
            queue = nullptr;
        }
    }

    if (getCurrentScene() != nullptr)
    {
        getCurrentScene()->update();
    }
}

void initScene()
{
    clearSprites();
    clearAnimations();
}

Scene* getCurrentScene()
{
    return current;
}

void reloadCurrentScene()
{
    loadScene(current);
}