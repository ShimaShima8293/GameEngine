#ifdef TEST
#define NCONSOLE
#include "gameEngine.h"
Entity bg;
Entity bg2;

int windowWidth = 1920;
int windowHeight = 1080;

int anmTest(Entity* entity, int frame, int len);

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
        //addEntity(&bg2);

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

        playEntityAnimation(&bg, anmTest);
    }
} sceneTest;

int anmTest(Entity* entity, int frame, int len)
{
    entity->changePos(0.1, 0.1);
    return 0;
}

int main(int argc, char* args[])
{
    init("グラデ～ション", windowWidth, windowHeight, INIT_ANTIALIASING);
    //
    //setFullscreenResolution(2880, 1800);

    //loadScene(&sceneTest);

    //startMainloop();

    printFatalError("");
    printFatalError("");

    return 0;
}

#endif