#pragma once

#include "internal.h"
#include "utilities/vector.h"
#include "render/Layer.h"

namespace GameEngine
{
    class Effect
    {
    public:
        Effect(Vec2 position, Layer& layer);

        virtual ~Effect() {}

        virtual int Update(Vec2 cameraPos) = 0;

        void Process();

    protected:
        Vec2 position;
        int frame;
        Layer& layer;
    };
}
