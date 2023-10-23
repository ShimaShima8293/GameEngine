#pragma once
#include "internal.h"
#include "sprite.h"

typedef int (*AnimationFunc)(int frame, int len);
typedef int (*SpriteAnimationFunc)(Sprite* sprite, int frame, int len);

size_t getAnimationCount();

void processAnimations();

void playAnimation(AnimationFunc func, int len = 0, bool reversed = false);

void playSpriteAnimation(Sprite* sprite, SpriteAnimationFunc func, int len = 0, bool reversed = false);

void stopAnimation(AnimationFunc func);

void stopSpriteAnimation(SpriteAnimationFunc func);

void clearAnimations();

void setGlobalAnimationSpeed(float speed);

float getGlobalAnimationSpeed();
