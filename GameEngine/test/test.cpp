#ifdef TEST
#include "core/Game.h"
#include "sprite/Sprite.h"

namespace GE = GameEngine;

std::unique_ptr<GE::Game> game;
GE::Window* window;

class SceneTest : public GE::Scene
{
public:
    SceneTest() :
        GE::Scene(),
        sprite(*window)
    {
        sprite.CreateSolid(10, 10);
        sprite.SetPos(100, 100);
    }

    void Update()
    {
        GE::PrintInfo("test working!");
    }

private:
    GE::Sprite sprite;
};

int main(int argc, char* args[])
{
    game = std::make_unique<GE::Game>(0);

    window = game->MakeWindow("Game Engine Test", 1280, 720);
    window->
    window->LoadScene<SceneTest>();

    game->MainLoop();

    return 0;
}
#endif