#include "Window.h"

namespace GameEngine
{
    Window::Window(std::string title, int width, int height) :
        gameWidth(width),
        gameHeight(height),
        renderer(nullptr),
        window(nullptr)
    {
        window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
        if (window == nullptr)
        {
            PrintFatalErrorInternal("init: Failed to create a window.");
            PrintSDLError();
            return;
        }
        SDL_DisplayMode mode{};
        SDL_GetWindowDisplayMode(window, &mode);
        mode.refresh_rate = 60;
        SDL_SetWindowDisplayMode(window, &mode);

        SDL_GetWindowDisplayMode(window, &mode);
        if (mode.refresh_rate == 60)
        {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        }
        else
        {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        }

        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);
        SDL_RenderClear(renderer);
    }

    void Window::SetTitle(std::string title)
    {
        SDL_SetWindowTitle(this->window, title.c_str());

    }

    int Window::LoadScene(std::unique_ptr<Scene> scene)
    {
        currentScene = std::move(scene);

        return 0;
    }

    void Window::Update()
    {
        if (this->GetFocus() == true)
        {
            currentScene->Update();
        }
    }

    bool Window::GetFocus()
    {
        return true;
    }

    GE_HWND Window::GetHWND()
    {
#ifdef _WIN32
        SDL_SysWMinfo wmInfo{};
        SDL_VERSION(&wmInfo.version);
        SDL_GetWindowWMInfo(this->window, &wmInfo);
        HWND hwnd = wmInfo.info.win.window;
        return hwnd;
#else
        PrintErrorInternal("getHWND: Unsupported OS.");
        return nullptr;
#endif
    }
    WindowDebugInfo Window::GetDebugInfo()
    {
        return this->debugInfo;
    }

    void Window::SetDebugInfo(WindowDebugInfo debugInfo)
    {
        this->debugInfo = debugInfo;
    }
    int Window::GetGameWidth()
    {
        return this->gameWidth;
    }
    int Window::GetGameHeight()
    {
        return this->gameHeight;
    }
    SDL_Renderer* Window::GetSDLRenderer()
    {
        return this->renderer;
    }
}