#ifdef TEST
#include "gameEngine.h"

Entity bg;

int main(int argc, char* args[])
{
    int windowWidth = 1920;
    int windowHeight = 1080;

    init("", windowWidth, windowHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE, true, false);

    SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, windowWidth, windowHeight, 32, SDL_PIXELFORMAT_RGBA32);
    Uint32* pixels = (Uint32*)surface->pixels;
    for (int y = 0; y < windowHeight; y++)
    {
        for (int x = 0; x < windowWidth; x++)
        {
            pixels[y * windowWidth + x] = SDL_MapRGBA(
                surface->format,
                roundToInt((float)y / windowHeight * 255),
                roundToInt(255 - (float)x / windowWidth * 255),
                roundToInt((float)x / windowWidth * 255),
                255
            );
        }
    }

    bg.loadFromSurface(surface);
    bg.stretchToWindow();
    addEntity(&bg);

    while (getRunning())
    {
        processEvents();

        if (!getWindowFocus())
        {
            SDL_Delay(1000 / 60);
            continue;
        }

        processScene();

        processUpdates();

        processAnimations();

        renderEverything();
    }

    closeResources();
    close();

    return 0;
}

#endif