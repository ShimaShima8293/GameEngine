#pragma once
#include "internal.h"

namespace GameEngine
{
    class Scene
    {
    public:
        virtual void Update() {}
        virtual ~Scene() {}
    };
}