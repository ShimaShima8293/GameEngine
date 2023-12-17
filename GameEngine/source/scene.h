#pragma once
#include "internal.h"

namespace GameEngine
{

    // This is an interface for the scene feature.
    class Scene
    {
    public:
        // This virtual function will be called when `processScene()` is called after `loadScene()` is called.
        virtual void start() {}
        // This virtual function will be called every frame when `processScene()` is called.
        virtual void update() {}
        // This virtual function will be called when another scene is loaded.
        virtual void free() {}
    };

    // Use this function to load a scene. Don't use Scene::start() manually...
    void loadScene(Scene* scene);

    // Call this function every frame to process scenes and actually load and use the scenes.
    void processScene();

    // Call this to get the current Scene class.
    Scene* getCurrentScene();

    // Reload the current scene.
    void reloadCurrentScene();

    // Unload the current scene.
    void unloadCurrentScene();

}