#include "Effect.h"

namespace GameEngine
{
    Effect::Effect(Vec2 position, Layer& layer) :
        position(position),
        layer(layer),
        frame(0)
    {
    }
    void Effect::Process()
    {
        frame++;
    }
}