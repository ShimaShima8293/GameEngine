﻿#ifdef TEST
//#define NCONSOLE
#include "gameEngine.h"
Entity text;

int windowWidth = 2880;
int windowHeight = 1800;

int anmTest(Entity* entity, int frame, int len);

static class SceneTest : public Scene
{
public:
    void start()
    {

    }
    void update()
    {
    }
} sceneTest;

int anmTest(Entity* entity, int frame, int len)
{
    //entity->changePos(0.1, 0.1);
    return 0;
}

int main(int argc, char* args[])
{
    init("GameEngine test", windowWidth, windowHeight, INIT_DISABLE_DEBUGGING);

    setFullscreenResolution(2880, 1800);

    loadScene(&sceneTest);

    startMainloop();

    return 0;
}

#endif