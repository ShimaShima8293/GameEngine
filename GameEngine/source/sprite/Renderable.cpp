#include "Renderable.h"
#include "../render.h"

namespace GameEngine
{
    Renderable::~Renderable()
    {
        removeSprite(this);
    }
}