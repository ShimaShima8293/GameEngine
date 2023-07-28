#ifdef TEST
#define NCONSOLE
#include "gameEngine.h"
Entity enemy;
Entity player;

int windowWidth = 1920;
int windowHeight = 1080;

int anmTest(Entity* entity, int frame, int len);

static class SceneTest : public Scene
{
public:
    void start()
    {
        enemy.createSolid(20, 20, { 255, 0, 0, 255 });
        enemy.setPosCentered();
        addEntity(&enemy);

        player.createSolid(20, 20, { 0, 255, 0, 255 });
        player.setPosCentered();
        addEntity(&player);
    }
    void update()
    {
        if (getKeyPressed(SDLK_UP))
        {
            player.changePos(0.0f, -5.0f);
        }
        if (getKeyPressed(SDLK_DOWN))
        {
            player.changePos(0.0f, 5.0f);
        }
        if (getKeyPressed(SDLK_LEFT))
        {
            player.changePos(-5.0f, 0.0f);
        }
        if (getKeyPressed(SDLK_RIGHT))
        {
            player.changePos(5.0f, 0.0f);
        }
        enemy.moveTo(2.0f, 90.0f - atan2(player.getCY() - enemy.getCY(), player.getCX() - enemy.getCX()) * (180.0f / 3.14f));
    }
} sceneTest;

int anmTest(Entity* entity, int frame, int len)
{
    //entity->changePos(0.1, 0.1);
    return 0;
}

int main(int argc, char* args[])
{
    init("グラデ～ション", windowWidth, windowHeight, INIT_ANTIALIASING);

    setFullscreenResolution(2880, 1800);

    loadScene(&sceneTest);

    startMainloop();

    return 0;
}

#endif