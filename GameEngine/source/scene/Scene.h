#pragma once

#include "internal.h"

namespace GameEngine
{
    class Scene
    {
    public:
        Scene() {}

        virtual void Update() = 0;

        virtual ~Scene() {}
    };
}