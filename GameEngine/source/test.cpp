#ifdef TEST
#include "gameEngine.h"

int main(int argc, char* args[])
{
    init("Hello!", 1920, 1080, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE, true, false);

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