#pragma once
#include "internal.h"

#include "sprite/Renderable.h"
#include "sprite/Sprite.h"

#include <memory>
#include <vector>

namespace GameEngine
{
    class Renderer;
    class DebugOutput;

    class Layer
    {
    public:
        Layer(Renderer& renderer, DebugOutput& output);
        
        ~Layer();

        void Add(std::shared_ptr<Renderable> sprite);

        std::shared_ptr<Sprite> CreateFromImage(std::string path);

        void Render();

    private:
        Renderer& renderer;

        DebugOutput& output;

        std::vector<std::shared_ptr<Renderable>> sprites;
    };
}