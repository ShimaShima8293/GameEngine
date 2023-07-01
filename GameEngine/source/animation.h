#pragma once

typedef void (*AnimationFunc)(int frame, int len);

struct AnimationData
{
    AnimationFunc func;
    int frame;
    int len;
    bool reversed;
};

size_t getAnimationCount();

void processAnimations();

void playAnimation(AnimationFunc func, int len, bool reversed = false);

void stopAnimation(AnimationFunc func);

void clearAnimations();
