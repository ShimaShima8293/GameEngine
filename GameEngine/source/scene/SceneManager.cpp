#include "SceneManager.h"

namespace GameEngine
{
    SceneManager::SceneManager()
    {
    }

    void SceneManager::Load(std::unique_ptr<Scene> scene)
    {
        newScene = std::move(scene);
    }

    void SceneManager::Process()
    {
        if (newScene)
        {
            if (currentScene)
            {
                Unload();
            }

            currentScene = std::move(newScene);
        }
    }

    void SceneManager::Unload()
    {
        currentScene.reset();
    }
}