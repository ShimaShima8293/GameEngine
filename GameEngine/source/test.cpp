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
    void Start()
    {
        child1.CreateSolid(100, 100, { 255, 0, 0, 255 });
        child1.SetPos(100, 50);
        child2.CreateSolid(100, 100, { 0, 255, 0, 255 });
        group.AddChild(&child1);
        group.AddChild(&child2);
        AddSprite(&group);
    }
    void Update()
    {
        if (GetKeyPressed(SDLK_UP))
        {
            group.ChangePos(0.0f, -1.0f);
        }
        if (GetKeyPressed(SDLK_DOWN))
        {
            group.ChangePos(0.0f, 1.0f);
        }
        if (GetKeyPressed(SDLK_RIGHT))
        {
            group.ChangeSize(-1.0f, -1.0f);
        }
        if (GetKeyPressed(SDLK_LEFT))
        {
            group.ChangeSize(1.0f, 1.0f);
        }

        if (GetKeyPressed(SDLK_1))
        {
            group.SetAlpha(group.GetAlpha() - 1);
            PrintInfo("Group alpha: " + std::to_string(group.GetAlpha()));
        }
        if (GetKeyPressed(SDLK_2))
        {
            group.SetAlpha(group.GetAlpha() + 1);
            PrintInfo("Group alpha: " + std::to_string(group.GetAlpha()));
        }

        if (GetKeyPressed(SDLK_3))
        {
            child1.SetAlpha(child1.GetAlpha() - 1);
            PrintInfo("Child alpha: " + std::to_string(child1.GetAlpha()));
        }
        if (GetKeyPressed(SDLK_4))
        {
            child1.SetAlpha(child1.GetAlpha() + 1);
            PrintInfo("Child alpha: " + std::to_string(child1.GetAlpha()));
        }
    }
} sceneTest;

int main(int argc, char* args[])
{
    Init("GameEngine test", 1920, 1080, 0);

    LoadScene(&sceneTest);

    Mainloop();

    return 0;
}

#endif