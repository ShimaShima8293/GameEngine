#pragma once

#include "Layer.h"

#include "internal.h"
#include "sprite/Renderable.h"

#include <memory>
#include <vector>

struct SDL_Renderer;

namespace GameEngine
{
    class Window;

    class Renderer
    {
    public:
        struct DebugMode
        {
            bool showInfo;
            bool showBorders;
        };

        Renderer(Window& window, int width, int height, DebugOutput& output);

        ~Renderer();

        void AddLayer(std::shared_ptr<Layer> layer);

        void ClearAll();

        void Render();

        SDL_Renderer* GetSDLRenderer();

        const DebugMode GetDebugMode() const;

        void SetDebugMode(DebugMode debugMode);

        const int GetWidth() const;

        const int GetHeight() const;

    private:
        Window& window;
        SDL_Renderer* renderer;
        DebugMode debugMode;
        DebugOutput& output;

        std::vector<std::shared_ptr<Layer>> layers;

        int width, height;
    };
}