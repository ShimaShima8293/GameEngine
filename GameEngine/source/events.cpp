#include "events.h"
#include <map>
#include "vars.h"
#include "audio.h"
#include "scene.h"

bool focused = false;
bool mouseMoved = false;
std::map<SDL_Keycode, bool> keyPressed;
std::map<SDL_Keycode, bool> keyPressedPulse;
std::map<Uint8, bool> buttonPressed;
std::map<Uint8, bool> buttonPressedPulse;
std::map<Uint8, bool> joyPressed;
std::map<Uint8, bool> joyPressedPulse;
int mouseX = 0, mouseY = 0;
bool running = true;
int globalFrame = 0;

void processEvents()
{
    SDL_Event event;
    mouseMoved = false;
    keyPressedPulse.clear();
    buttonPressedPulse.clear();
    while (SDL_PollEvent(&event))
    {
        if (event.window.event == SDL_WINDOWEVENT_FOCUS_LOST)
        {
            focused = false;
            printInfo("Focus lost");
        }
        if (event.window.event == SDL_WINDOWEVENT_FOCUS_GAINED)
        {
            focused = true;
            printInfo("Focus gained");
        }
        if (event.type == SDL_QUIT)
        {
            running = false;
        }
        if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
        {
            keyPressed[event.key.keysym.sym] = true;
            keyPressedPulse[event.key.keysym.sym] = true;
        }
        if (event.type == SDL_KEYUP)
        {
            keyPressed[event.key.keysym.sym] = false;
        }
        if (event.type == 8192)
        {
            SDL_GetWindowSize(window, &screenWidth, &screenHeight);
        }
        if (event.type == SDL_MOUSEMOTION)
        {
            SDL_GetMouseState(&mouseX, &mouseY);
            mouseMoved = true;
        }
        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            buttonPressed[event.button.button] = true;
            buttonPressedPulse[event.button.button] = true;
        }
        if (event.type == SDL_MOUSEBUTTONUP)
        {
            buttonPressed[event.button.button] = false;
        }
        if (event.type == SDL_JOYBUTTONDOWN)
        {
            joyPressed[event.jbutton.button] = true;
            printInfo(event.jbutton.button);
        }
        if (event.type == SDL_JOYBUTTONUP)
        {
            joyPressed[event.jbutton.button] = false;
            printInfo(event.jbutton.button);
        }
    }

    if (getKeyPressedPulse(SDLK_F11) && !getKeyPressed(SDLK_LSHIFT) && !fullscreenLocked)
    {
        SDL_SetWindowFullscreen(window, fullscreen ? 0 : SDL_WINDOW_FULLSCREEN);
        fullscreen = !fullscreen;
        printInfo((fullscreen ? "Entered fullscreen" : "Exited fullscreen"));
        windowMode = fullscreen ? "Full screen" : "Windowed";
    }
    if (getKeyPressedPulse(SDLK_F11) && getKeyPressed(SDLK_LSHIFT) && !fullscreenLocked)
    {
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
        fullscreen = true;
        printInfo("Maximized window");
        windowMode = "Maximized";

    }
    if (getKeyPressedPulse(SDLK_F3))
    {
        debug = !debug;
    }
    if (getKeyPressedPulse(SDLK_m))
    {
        setMuteState(!getMuteState());
    }

    if (getKeyPressedPulse(SDLK_F4))
    {
        reloadCurrentScene();
    }
}

bool getWindowFocus()
{
    return focused;
}

void setWindowFocus(bool _focused)
{
    focused = _focused;
}

bool getKeyPressed(SDL_KeyCode code)
{
    return keyPressed[code];
}

bool getKeyPressedPulse(SDL_KeyCode code)
{
    return keyPressedPulse[code];
}

bool getRunning()
{
    return running;
}

void close()
{
    running = false;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int getWindowWidth()
{
    return windowWidth;
}

int getWindowHeight()
{
    return windowHeight;
}

bool fullscreenLocked = false;

void init(std::string windowTitle, int _windowWidth, int _windowHeight, int _windowFlags, bool _debug, bool renderQuality)
{
    debug = _debug;
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        printFatalError("Failed to initialize SDL... SDL Error: " << SDL_GetError());
    }
    if (IMG_Init(0) < 0)
    {
        printFatalError("Failed to initialize SDL_Image... SDL_image Error: " << IMG_GetError());
    }
    if (TTF_Init() < 0)
    {
        printFatalError("Failed to initialize SDL_TTF... SDL_ttf Error: " << TTF_GetError());
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) != 0)
    {
        printFatalError("Failed to initialize SDL_Mixer... SDL_mixer Error: " << Mix_GetError());
    }

    if (_windowFlags & SDL_WINDOW_FULLSCREEN)
    {
        fullscreenLocked = true;
        windowMode = "Full screen (locked)";
    }


    window = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _windowWidth, _windowHeight, _windowFlags);

#ifdef NDEBUG
    if (!fullscreenLocked)
    {
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    }
#endif

    if (renderQuality)
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    antialiasing = renderQuality;


    SDL_DisplayMode mode;

    SDL_GetWindowDisplayMode(window, &mode);
    if (mode.refresh_rate == 60)
    {
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        vsync = true;
    }
    else
    {
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        vsync = false;
    }

    printInfo("Display Info");
    printInfo("  - Width: " << mode.w << " pixels");
    printInfo("  - Height: " << mode.h << " pixels");
    printInfo("  - Refresh rate: " << (mode.refresh_rate == 0 ? "VSync not supported" : (std::to_string(mode.refresh_rate) + " frames per second").c_str()));
    printInfo("  - Supports VSync: " << (mode.refresh_rate == 0 ? "No" : "Yes"));
    printInfo("  - VSync: " << (vsync ? "On (60 fps)" : "Off (not 60fps)"));
    printInfo("SDL Versions");
    printInfo("  - SDL version: " << SDL_MAJOR_VERSION << "." << SDL_MINOR_VERSION << "." << SDL_PATCHLEVEL);
    printInfo("  - SDL_image version: " << SDL_IMAGE_MAJOR_VERSION << "." << SDL_IMAGE_MINOR_VERSION << "." << SDL_IMAGE_PATCHLEVEL);
    printInfo("  - SDL_ttf version: " << SDL_TTF_MAJOR_VERSION << "." << SDL_TTF_MINOR_VERSION << "." << SDL_TTF_PATCHLEVEL);
    printInfo("  - SDL_mixer version: " << SDL_MIXER_MAJOR_VERSION << "." << SDL_MIXER_MINOR_VERSION << "." << SDL_MIXER_PATCHLEVEL);


    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);
    SDL_RenderClear(renderer);

    TTF_Font* debugFont = TTF_OpenFont("/Windows/Fonts/arial.ttf", 40);
    if (debugFont == NULL)
    {
        printFatalError("Failed to create debugFont");
    }

    debugText.setName("debugText");
    debugText.loadFromText(DEFAULT_TEXT, debugFont);
    debugText.setPos(0, 0);

    running = true;
    SDL_GetWindowSize(window, &screenWidth, &screenHeight);
}
