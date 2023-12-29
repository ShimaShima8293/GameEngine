#include "scene.h"
#include "events.h"
#include "render.h"
#include "animation.h"

namespace GameEngine
{
    Scene* queue;
    Scene* current;

    void LoadScene(Scene* scene)
    {
        queue = scene;
    }

    void ProcessScene()
    {
        if (queue != nullptr)
        {
            if (current != nullptr)
            {
                current->Free();
            }

            ClearSprites();
            ClearAnimations();
            PrintInfoGE("ProcessScene: Loading a scene.");
            current = queue;
            queue->Start();
            if (current == queue)
            {
                queue = nullptr;
            }
        }

        if (GetCurrentScene() != nullptr)
        {
            GetCurrentScene()->Update();
        }
    }

    Scene* GetCurrentScene()
    {
        return current;
    }

    void ReloadCurrentScene()
    {
        if (current == nullptr)
        {
            PrintErrorGE("ReloadCurrentScene: Scene is not loaded.");
            return;
        }

        LoadScene(current);
    }

    void UnloadCurrentScene()
    {
        if (current == nullptr)
        {
            PrintErrorGE("UnloadCurrentScene: Scene is not loaded.");
            return;
        }

        current->Free();
        current = nullptr;

        ClearSprites();
        ClearAnimations();
    }

}