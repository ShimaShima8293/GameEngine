#pragma once

#include <iostream>
#include <vector>

// Interface for scenes
class Scene
{
public:
    virtual void start();
    virtual void update();
    virtual void free();
};

// Use this function to load a scene. Don't use Scene::start() manually...
void loadScene(Scene* scene);
// Call this function every frame
void processScene();
// Call this to get the current Scene class.
Scene* getCurrentScene();
// Initializes lists. Call this function every time you start a scene.
void initScene();
// Reload the current scene.
void reloadCurrentScene();