#include "Window.h"
#include <SDL.h>
#include <SDL_syswm.h>

namespace GameEngine
{
    Window::Window(std::string title, int width, int height, DebugOutput& output) :
        sceneManager(),
        mode(WINDOWED),
        output(output),
        isOpen(true),
        focused(true)
    {
        output.InfoGE("Creating window.");

        window = SDL_CreateWindow(
            title.c_str(),
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            width,
            height,
            SDL_WINDOW_RESIZABLE
        );

        if (window == nullptr)
        {
            output.ErrorGE("Window::Window: Failed to create window.");
            output.SDLError();
            return;
        }

        renderer = std::make_unique<Renderer>(*this, width, height, output);

        output.InfoGE("Window created! Welcome to Game Engine v1.0!");
    }

    Window::~Window()
    {
        if (window != nullptr)
        {
            SDL_DestroyWindow(window);
        }
    }

    DebugOutput& Window::GetOutput()
    {
        return output;
    }

    Input& Window::GetInput()
    {
        return input;
    }

    SDL_Window* Window::GetSDLWindow()
    {
        return this->window;
    }

    void Window::LoadScene(std::unique_ptr<Scene> scene)
    {
        output.InfoGE("Loading a scene.");
        sceneManager.Load(std::move(scene));
    }

    Renderer& Window::GetRenderer()
    {
        return *renderer;
    }

    void Window::Update()
    {
        this->ProcessEvents();

        if (focused)
        {
            renderer->Render();
        }
    }

    void Window::ProcessEvents()
    {
        SDL_Event event{};

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
            {
                this->EndMainloop();
                break;
            }
            case SDL_WINDOWEVENT:
            {
                switch (event.window.event)
                {
                case SDL_WINDOWEVENT_FOCUS_LOST:
                {
                    focused = false;
                    output.InfoGE("Window lost focus.");
                    break;
                }
                case SDL_WINDOWEVENT_FOCUS_GAINED:
                {
                    focused = true;
                    output.InfoGE("Window gained focus.");
                    break;
                }
                }
                break;
            }
            default:
            {
                break;
            }
            }
        }
    }

    const bool Window::IsOpen() const
    {
        return isOpen;
    }

    void Window::EndMainloop()
    {
        isOpen = false;
        output.InfoGE("Ending mainloop.");
    }

    GAMEENGINE_HWND Window::GetHWND()
    {
#ifdef _WIN32
        SDL_SysWMinfo wmInfo{};
        SDL_VERSION(&wmInfo.version);
        SDL_GetWindowWMInfo(this->GetSDLWindow(), &wmInfo);

        HWND hwnd = wmInfo.info.win.window;
        return hwnd;
#else
        output.ErrorGE("GetHWND: Unsupported OS.");
        return nullptr;
#endif
    }

    Window::Mode Window::GetMode()
    {
        return mode;
    }

    void Window::SetMode(Window::Mode mode)
    {
        SDL_SetWindowFullscreen(window, mode);

        this->mode = mode;

        output.InfoGE("Window mode changed.");
    }

}