#include "Renderable.h"
#include "../render.h"

namespace GameEngine
{
    Renderable::~Renderable()
    {
        RemoveSprite(this);
    }
}