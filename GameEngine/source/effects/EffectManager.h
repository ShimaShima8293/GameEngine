/*
*  effects.h
*
*  Functions for Playing effects. Write scripts in `effectScripts.cpp`
*  Ported from Project18.
*
*/

#pragma once
#include "Effect.h"

#include <vector>
#include <memory>

namespace GameEngine
{
    class EffectManager
    {
    private:
        std::vector<std::unique_ptr<Effect>> effects{};
        Layer& layer;

    public:
        EffectManager(Layer& layer);
        
        void Add(std::unique_ptr<Effect> effect);

        void Process(Vec2 cameraPos);

        void RemoveAll();
    };
}