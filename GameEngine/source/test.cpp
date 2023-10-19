#ifdef TEST
//#define NCONSOLE
#include "gameEngine.h"
Sprite text;
Sprite cursor;

int windowWidth = 1920;
int windowHeight = 1080;

int anmTest(Sprite* sprite, int frame, int len);

static class SceneTest : public Scene
{
public:
    void start()
    {
        cursor.createSolid(0, 0);
        cursor.setScale(16.0f, 16.0f);
        addSprite(&cursor);
    }
    void update()
    {
        cursor.setCPos(getCursorPos());
        cursor.setColor(255, 255, 255);
        if (getKeyPressed(SDLK_SPACE))
        {
            cursor.setCPos(getCursorWindowPos());
        }
        if (getMouseButton(1))
        {
            cursor.setColor(255, 0, 0);
        }
        if (getJoyAxisPulse(0, AXIS_NEGATIVE, 200))
        {
            printInfo("PRESSED!");
        }
        //printInfo(std::to_string(getCursorWindowPos().x) + ":" + std::to_string(getCursorWindowPos().y));
    }
} sceneTest;

int anmTest(Sprite* sprite, int frame, int len)
{
    //sprite->changePos(0.1, 0.1);
    return 0;
}

int main(int argc, char* args[])
{
    init("GameEngine test", 640, 480, 0);

    //setFullscreenResolution(640, 480);

    setConsoleLogLevel(PRINT_EVERYTHING);
    setPopupLogLevel(PRINT_EVERYTHING);

    loadScene(&sceneTest);

    startMainloop();

    return 0;
}

#endif