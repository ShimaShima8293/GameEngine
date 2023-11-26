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
            group.changePos(1.0f, 0.0f);
        }
        if (getKeyPressed(SDLK_LEFT))
        {
            group.changePos(-1.0f, 0.0f);
        }
        group.render({});
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