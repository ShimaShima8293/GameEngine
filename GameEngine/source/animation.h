#pragma once
#include "internal.h"
#include "sprite.h"

namespace GameEngine
{

    typedef int (*AnimationFunc)(int frame, int len);
    typedef int (*SpriteAnimationFunc)(Renderable* sprite, int frame, int len);

    class Animation
    {
    public:
        virtual void start() {}
        virtual int update(int frame, int len) {}
        virtual void free() {}
    };

    size_t getAnimationCount();

    void processAnimations();

    void playAnimation(AnimationFunc func, int len = 0, bool reversed = false);
    void playAnimation(Animation animation, int len = 0, bool reversed = false);

    void playSpriteAnimation(Renderable* sprite, SpriteAnimationFunc func, int len = 0, bool reversed = false);

    void stopAnimation(AnimationFunc func);

    void stopSpriteAnimation(SpriteAnimationFunc func);

    void clearAnimations();

    void setGlobalAnimationSpeed(float speed);

    float getGlobalAnimationSpeed();

}