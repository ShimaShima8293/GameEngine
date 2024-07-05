#include "effects.h"
#include "EffectManager.h"

namespace GameEngine
{
    EffectManager::EffectManager(Layer& layer) : 
        layer(layer)
    {
        
    }

    void EffectManager::Add(std::unique_ptr<Effect> effect)
    {
        effects.push_back(std::move(effect));
    }

    void EffectManager::Process(Vec2 cameraPos)
    {
        for (int i = 0; i < effects.size(); i++)
        {
            effects[i]->Process();
            int result = effects[i]->Update(cameraPos);
            if (result != 0)
            {
                effects.erase(effects.begin() + i);
                i--;
            }
        }
    }

    void EffectManager::RemoveAll()
    {
        effects.clear();
    }
}