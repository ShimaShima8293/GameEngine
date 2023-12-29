#pragma once
#include "internal.h"
#include "sprite.h"

namespace GameEngine
{

    typedef int (*AnimationFunc)(int frame, int len);
    typedef int (*SpriteAnimationFunc)(Renderable* sprite, int frame, int len);

    size_t GetAnimationCount();

    void ProcessAnimations();

    void PlayAnimation(AnimationFunc func, int len = 0, bool reversed = false);

    void PlaySpriteAnimation(Renderable* sprite, SpriteAnimationFunc func, int len = 0, bool reversed = false);

    void StopAnimation(AnimationFunc func);

    void StopSpriteAnimation(SpriteAnimationFunc func);

    void ClearAnimations();

    void SetGlobalAnimationSpeed(float speed);

    float GetGlobalAnimationSpeed();

}