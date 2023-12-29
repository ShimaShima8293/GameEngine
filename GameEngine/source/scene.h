#pragma once
#include "internal.h"

namespace GameEngine
{

    // This is an interface for the scene feature.
    class Scene
    {
    public:
        virtual ~Scene() {}
        // This virtual function will be called when `ProcessScene()` is called after `LoadScene()` is called.
        virtual void Start() {}
        // This virtual function will be called every frame when `ProcessScene()` is called.
        virtual void Update() {}
        // This virtual function will be called when another scene is loaded.
        virtual void Free() {}
    };

    // Use this function to load a scene. Don't use Scene::Start() manually...
    void LoadScene(Scene* scene);

    // Call this function every frame to process scenes and actually load and use the scenes.
    void ProcessScene();

    // Call this to get the current Scene class.
    Scene* GetCurrentScene();

    // Reload the current scene.
    void ReloadCurrentScene();

    // Unload the current scene.
    void UnloadCurrentScene();

}