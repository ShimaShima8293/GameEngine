#pragma once

#include "Renderer.h"

#include "internal.h"
#include "debugging/DebugOutput.h"
#include "input/Input.h"
#include "scene/SceneManager.h"

#include <string>
#include <memory>

#ifdef _WIN32
struct HWND__;
typedef HWND__* HWND;
#define GAMEENGINE_HWND HWND
#else
#define GAMEENGINE_HWND void*
#endif

struct SDL_Window;

namespace GameEngine
{
    class Window
    {
    public:
        Window(std::string title, int width, int height, DebugOutput& output);

        ~Window();

        DebugOutput& GetOutput();
        
        Input& GetInput();

        SDL_Window* GetSDLWindow();

        void LoadScene(std::unique_ptr<Scene> scene);

        Renderer& GetRenderer();

        void Update();

        void ProcessEvents();

        const bool IsOpen() const;

        void EndMainloop();

        GAMEENGINE_HWND GetHWND();

        enum Mode
        {
            WINDOWED = 0,
            FULLSCREEN = 1,
            FULLSCREEN_DESKTOP = 4097
        };

        Window::Mode GetMode();

        void SetMode(Window::Mode mode);

        static const int DEFAULT_WIDTH = 1920;
        static const int DEFAULT_HEIGHT = 1080;

    private:
        SDL_Window* window;

        bool isOpen;
        bool focused;

        std::unique_ptr<Renderer> renderer;

        DebugOutput& output;
        
        SceneManager sceneManager;

        Input input;

        Window::Mode mode;
    };
}