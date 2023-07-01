#pragma once

typedef void (*AnimationFunc)(int frame, int len);

struct AnimationData
{
    AnimationFunc func;
    int frame;
    int len;
};

size_t getAnimationCount();

void processAnimations();

void playAnimation(AnimationFunc func, int len);

void stopAnimation(AnimationFunc func);

void clearAnimations();
