#ifdef TEST
#include "gameEngine.h"

using namespace GameEngine;

TTF_Font* font = nullptr;

static class SceneTest : public Scene
{
private:
    Sprite image{};
    int size = 3;
    int random = 5;
public:
    void createImage()
    {
        SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, getGameWidth() / size, getGameHeight() / size, 32, SDL_PIXELFORMAT_RGBA32);
        Uint32* pixels = (Uint32*)surface->pixels;
        for (int i = 0; i < surface->w * surface->h; i++)
        {
            if (i > 0)
            {
                Uint8 pr, pg, pb, pa;
                SDL_GetRGBA(pixels[i - 1], surface->format, &pr, &pg, &pb, &pa);
                Uint8 r = pr + rand() % random;
                Uint8 g = pg + rand() % random;
                Uint8 b = pb + rand() % random;
                pixels[i] = SDL_MapRGBA(surface->format, r, g, b, 255);
            }
        }
        image.createFromSurface(surface);
        image.stretchToWindow();
    }
    void start()
    {
        createImage();
        addSprite(&image);
    }
    void update()
    {
        if (getKeyPressedPulse(SDLK_SPACE))
        {
            createImage();   
        }
        if (getKeyPressed(SDLK_RETURN))
        {
            createImage();
        }
        if (getKeyPressedPulse(SDLK_EQUALS))
        {
            size++;
            createImage();
        }
        if (getKeyPressedPulse(SDLK_MINUS))
        {
            size--;
            if (size < 1)
            {
                size = 1;
            }
            createImage();
        }
        if (getKeyPressedPulse(SDLK_PERIOD))
        {
            random++;
            createImage();
        }
        if (getKeyPressedPulse(SDLK_COMMA))
        {
            random--;
            if (random < 1)
            {
                random = 1;
            }
            createImage();
        }

        if (getKeyPressedPulse(SDLK_ESCAPE))
        {
            endMainloop();
        }
    }
} sceneTest;

int main(int argc, char* args[])
{
    init("GameEngine test", 3840, 2160, 0);

    setWindowMode(WindowMode::WINDOW_FULLSCREEN);
    hideCursor();

    loadScene(&sceneTest);

    startMainloop();

    return 0;
}

#endif