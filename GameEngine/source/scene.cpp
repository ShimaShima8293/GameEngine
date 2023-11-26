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

            initScene();
            printInfoGE("processScene: Loading a scene.");
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

}