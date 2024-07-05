#include "Renderer.h"
#include "Window.h"

#include "debugging/DebugOutput.h"

#include <SDL.h>

namespace GameEngine
{
    Renderer::Renderer(Window& window, int width, int height, DebugOutput& output) :
        window(window),
        renderer(nullptr),
        debugMode({false, false}),
        width(width),
        height(height),
        output(output)
    {
        renderer = SDL_CreateRenderer(window.GetSDLWindow(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        if (renderer == nullptr)
        {
            output.ErrorGE("Failed to create an SDL renderer.");
            output.SDLError();
            return;
        }
    }

    Renderer::~Renderer()
    {
        SDL_DestroyRenderer(renderer);
    }

    void Renderer::AddLayer(std::shared_ptr<Layer> layer)
    {
        layers.push_back(std::move(layer));
    }

    void Renderer::ClearAll()
    {
        layers.clear();
    }

    void Renderer::Render()
    {
        for (auto& layer : layers)
        {
            layer->Render();
        }

        SDL_RenderPresent(renderer);
    }

    SDL_Renderer* Renderer::GetSDLRenderer()
    {
        return renderer;
    }

    const Renderer::DebugMode Renderer::GetDebugMode() const
    {
        return debugMode;
    }

    void Renderer::SetDebugMode(DebugMode debugMode)
    {
        this->debugMode = debugMode;
    }

    const int Renderer::GetWidth() const
    {
        return width;
    }

    const int Renderer::GetHeight() const
    {
        return height;
    }


}