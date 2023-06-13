#include <iostream>
#include "macros.h"
#include "scene.h"
#include <vector>
#include "events.h"
#include "render.h"
#include "update.h"

Scene* queue;
Scene* current;

void loadScene(Scene* scene)
{
    queue = scene;
}

void processScene()
{
    if (queue != nullptr)
    {
        if (current != nullptr)
            current->free();

        initScene();
        queue->start();
        printInfo("Loaded scene at memory address      0x" << queue);
        current = queue;
        queue = nullptr;
    }
    if (getKeyPressedPulse(SDLK_F4))
    {
        queue = current;
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

void Scene::start()
{
}

void Scene::update()
{
}

void Scene::free()
{
}
