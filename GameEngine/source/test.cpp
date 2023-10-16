#ifdef TEST
//#define NCONSOLE
#include "gameEngine.h"
Sprite text;

int windowWidth = 1920;
int windowHeight = 1080;

int anmTest(Sprite* sprite, int frame, int len);

static class SceneTest : public Scene
{
public:
    void start()
    {

    }
    void update()
    {
        if (getJoyAxisPulse(0, AXIS_NEGATIVE, 200))
        {
            printInfo("PRESSED!");
        }
    }
} sceneTest;

int anmTest(Sprite* sprite, int frame, int len)
{
    //sprite->changePos(0.1, 0.1);
    return 0;
}

int main(int argc, char* args[])
{
    init("GameEngine test", 640, 480, INIT_DISABLE_DEBUGGING);

    //setFullscreenResolution(640, 480);

    loadScene(&sceneTest);

    startMainloop();

    return 0;
}

#endif