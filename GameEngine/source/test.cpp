#ifdef TEST
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
        SDL_Surface* input = IMG_Load("image.png");
        
        Uint32* pixels = (Uint32*)input->pixels;
        for (int y = 0; y < input->h; y++)
        {
            for (int x = 0; x < input->w; x++)
            {
                Uint8 r, g, b, a;
                SDL_GetRGBA(pixels[input->w * y + x], input->format, &r, &g, &b, &a);
                pixels[input->w * y + x] = SDL_MapRGBA(input->format, limit(r - 50, 0, 255), 0, 0, limit(a, 0, 255));
            }

        }
        //SDL_Surface* output = SDL_CreateRGBSurfaceWithFormat(0, input->w, input->h, 32, SDL_PIXELFORMAT_ARGB32);
        //SDL_BlitSurface(input, NULL, output, NULL);
        text.createFromSurface(input);
        text.stretchToWindow();
        addEntity(&text);

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
    init("グラデ～ション", windowWidth, windowHeight, INIT_ANTIALIASING);

    setFullscreenResolution(2880, 1800);

    loadScene(&sceneTest);

    startMainloop();

    return 0;
}

#endif