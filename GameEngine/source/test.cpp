#ifdef TEST
//#define NCONSOLE
#include "gameEngine.h"
Entity text;

int windowWidth = 1920;
int windowHeight = 1080;

int anmTest(Entity* entity, int frame, int len);

static class SceneTest : public Scene
{
public:
    void start()
    {
        //SDL_Surface* input = TTF_RenderUTF8_Blended_Wrapped(openFont("/Windows/Fonts/yumindb.ttf", 480), "Hello", { 255, 255, 255, 255 }, 0);
        //SDL_Surface* output = SDL_CreateRGBSurfaceWithFormat(0, input->w, input->h, 32, SDL_PIXELFORMAT_RGBA32);
        //text.createFromSurface(output);
        //addEntity(&text);

    }
    void update()
    {
        printInfo(getJoyAxis(0));
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