#ifdef TEST
#include "gameEngine.h"

using namespace GameEngine;

TTF_Font* font = nullptr;

static class SceneTest : public Scene
{
private:
    SpriteGroup group;
    Sprite child1;
    Sprite child2;
    int size = 3;
    int random = 5;
public:
    void start()
    {
        child1.createSolid(100, 100, { 255, 0, 0, 255 });
        child1.setPos(100, 50);
        child2.createSolid(100, 100, { 0, 255, 0, 255 });
        group.addChild(&child1);
        group.addChild(&child2);
        addSprite(&group);
    }
    void update()
    {
        if (getKeyPressed(SDLK_UP))
        {
            group.changePos(0.0f, -1.0f);
        }
        if (getKeyPressed(SDLK_DOWN))
        {
            group.changePos(0.0f, 1.0f);
        }
        if (getKeyPressed(SDLK_RIGHT))
        {
            group.changeSize(-1.0f, -1.0f);
        }
        if (getKeyPressed(SDLK_LEFT))
        {
            group.changeSize(1.0f, 1.0f);
        }

        if (getKeyPressed(SDLK_1))
        {
            group.setAlpha(group.getAlpha() - 1);
            printInfo("Group alpha: " + std::to_string(group.getAlpha()));
        }
        if (getKeyPressed(SDLK_2))
        {
            group.setAlpha(group.getAlpha() + 1);
            printInfo("Group alpha: " + std::to_string(group.getAlpha()));
        }

        if (getKeyPressed(SDLK_3))
        {
            child1.setAlpha(child1.getAlpha() - 1);
            printInfo("Child alpha: " + std::to_string(child1.getAlpha()));
        }
        if (getKeyPressed(SDLK_4))
        {
            child1.setAlpha(child1.getAlpha() + 1);
            printInfo("Child alpha: " + std::to_string(child1.getAlpha()));
        }
    }
} sceneTest;

int main(int argc, char* args[])
{
    init("GameEngine test", 1920, 1080, 0);

    loadScene(&sceneTest);

    startMainloop();

    return 0;
}

#endif