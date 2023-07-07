#ifdef TEST
#include "gameEngine.h"

Entity bg;
Entity bg2;

int windowWidth = 1920;
int windowHeight = 1080;

static class SceneTest : public Scene
{
public:
    void start()
    {
        Uint8 r1 = (Uint8)randomRange(0, 255);
        Uint8 g1 = (Uint8)randomRange(0, 255);
        Uint8 b1 = (Uint8)randomRange(0, 255);
        Uint8 r2 = (Uint8)randomRange(0, 255);
        Uint8 g2 = (Uint8)randomRange(0, 255);
        Uint8 b2 = (Uint8)randomRange(0, 255);

        bg.createGradient(
            windowHeight,
            { r1, g1, b1, 255 },
            { r2, g2, b2, 255 },
            VERTICAL
        );

        bg.stretchToWindow();
        addEntity(&bg);

        Uint8 r3 = (Uint8)randomRange(0, 255);
        Uint8 g3 = (Uint8)randomRange(0, 255);
        Uint8 b3 = (Uint8)randomRange(0, 255);
        Uint8 r4 = (Uint8)randomRange(0, 255);
        Uint8 g4 = (Uint8)randomRange(0, 255);
        Uint8 b4 = (Uint8)randomRange(0, 255);

        bg2.createGradient(
            windowWidth,
            { r3, g3, b3, 255 },
            { r4, g4, b4, 255 },
            HORIZONTAL
        );
        bg2.setAlpha(128);
        bg2.stretchToWindow();
        addEntity(&bg2);

        SDL_SetWindowTitle(
            getWindow(),
            ("グラデ～ション (" +
                std::to_string((int)r1) + ", " +
                std::to_string((int)g1) + ", " +
                std::to_string((int)b1) + ") -> (" +
                std::to_string((int)r2) + ", " +
                std::to_string((int)g2) + ", " +
                std::to_string((int)b2) + ") and (" +
                std::to_string((int)r3) + ", " +
                std::to_string((int)g3) + ", " +
                std::to_string((int)b3) + ") -> (" +
                std::to_string((int)r4) + ", " +
                std::to_string((int)g4) + ", " +
                std::to_string((int)b4) + ")"
                ).c_str()
        );
    }
} sceneTest;

void anmTest(int frame, int len)
{
    bg.setPos(randomRange(-10, 10), randomRange(-10, 10));
}

int main(int argc, char* args[])
{
    init("グラデ～ション", windowWidth, windowHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE, true, false);
    setWindowMode(WINDOW_FULLSCREEN);

    loadScene(&sceneTest);

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