#ifdef TEST
//#define NCONSOLE
#include "gameEngine.h"
GameEngine::Sprite text;
GameEngine::Sprite cursor;

int windowWidth = 1920;
int windowHeight = 1080;

int anmTest(GameEngine::Sprite* sprite, int frame, int len);

static class SceneTest : public GameEngine::Scene
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
        cursor.setCPos(GameEngine::getCursorPos());
        cursor.setColor(255, 255, 255);
        if (GameEngine::getKeyPressed(SDLK_SPACE))
        {
            cursor.setCPos(GameEngine::getCursorWindowPos());
        }
        if (GameEngine::getMouseButton(1))
        {
            cursor.setColor(255, 0, 0);
        }
        if (GameEngine::getJoyAxisPulse(0, GameEngine::AXIS_NEGATIVE, 200))
        {
            GameEngine::printInfo("PRESSED!");
        }
        //printInfo(std::to_string(getCursorWindowPos().x) + ":" + std::to_string(getCursorWindowPos().y));
    }
} sceneTest;

int anmTest(GameEngine::Sprite* sprite, int frame, int len)
{
    //sprite->changePos(0.1, 0.1);
    return 0;
}

int main(int argc, char* args[])
{
    GameEngine::init("GameEngine test", 640, 480, 0);

    //setFullscreenResolution(640, 480);

    GameEngine::setConsoleLogLevel(GameEngine::PRINT_EVERYTHING);

    loadScene(&sceneTest);

    GameEngine::startMainloop();

    return 0;
}

#endif