#pragma once

#include "Scene.h"

#include "internal.h"

#include <memory>

namespace GameEngine
{
    class Window;

    class SceneManager
    {
    public:
        SceneManager();

        void Load(std::unique_ptr<Scene> scene);

        void Process();

        void Unload();

    private:
        std::unique_ptr<Scene> currentScene;
        std::unique_ptr<Scene> newScene;
    };
}