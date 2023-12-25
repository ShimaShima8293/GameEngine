#pragma once
#include "internal.h"
#include "sprite.h"
#include "Animation.h"

namespace GameEngine
{
    typedef int (*AnimationFunc)(int frame, int len);
    typedef int (*SpriteAnimationFunc)(Renderable* sprite, int frame, int len);

    class AnimationPlayer
    {
    public:
        AnimationPlayer();

        size_t getAnimationCount();

        void processAnimations();

        void playAnimation(AnimationFunc func, int len = 0, bool reversed = false);

        template <typename T, typename = std::enable_if_t<std::is_base_of<Animation, T>::value>>
        inline void playAnimation(int len, bool reversed)
        {
            
        }

        void playSpriteAnimation(Renderable* sprite, SpriteAnimationFunc func, int len = 0, bool reversed = false);

        void stopAnimation(AnimationFunc func);

        void stopSpriteAnimation(SpriteAnimationFunc func);

        void clearAnimations();

        void setGlobalAnimationSpeed(float speed);

        float getGlobalAnimationSpeed();

    private:
        struct AnimationData
        {
            AnimationFunc func;
            int frame;
            int len;
            bool reversed;
        };

        struct SpriteAnimationData
        {
            Renderable* sprite;
            SpriteAnimationFunc func;
            int frame;
            int len;
            bool reversed;
        };

        std::vector<AnimationData> dataList;
        std::vector<AnimationData> playQueue;
        std::vector<AnimationFunc> stopQueue;

        std::vector<SpriteAnimationData> dataList2;
        std::vector<SpriteAnimationData> playQueue2;
        std::vector<SpriteAnimationFunc> stopQueue2;

        float animationSpeed = 1.0f;
    };


}