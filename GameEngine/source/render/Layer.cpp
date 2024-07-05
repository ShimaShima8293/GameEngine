#include "Layer.h"
#include "debugging/DebugOutput.h"

namespace GameEngine
{
    Layer::Layer(Renderer& renderer, DebugOutput& output) :
        renderer(renderer),
        output(output)
    {
    }

    Layer::~Layer()
    {
    }

    void Layer::Add(std::shared_ptr<Renderable> sprite)
    {
        sprites.push_back(sprite);
    }

    std::shared_ptr<Sprite> Layer::CreateFromImage(std::string path)
    {
        std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>(renderer, output);
        sprite->CreateFromImage(path);

        this->Add(sprite);

        return sprite;
    }

    void Layer::Render()
    {
        for (auto& sprite : sprites)
        {
            sprite->Render({});
        }
    }
}