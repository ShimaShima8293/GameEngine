#include "scene.h"
#include "events.h"
#include "render.h"
#include "animation.h"

namespace GameEngine
{
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
            {
                current->free();
            }

            clearSprites();
            clearAnimations();
            PrintInfoInternal("processScene: Loading a scene.");
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

    Scene* getCurrentScene()
    {
        return current;
    }

    void reloadCurrentScene()
    {
        if (current == nullptr)
        {
            PrintErrorInternal("reloadCurrentScene: Scene is not loaded.");
            return;
        }

        loadScene(current);
    }

    void unloadCurrentScene()
    {
        if (current == nullptr)
        {
            PrintErrorInternal("unloadCurrentScene: Scene is not loaded.");
            return;
        }

        current->free();
        current = nullptr;

        clearSprites();
        clearAnimations();
    }

}