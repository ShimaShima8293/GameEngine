#pragma once
#include "Entity.h"

typedef int (*AnimationFunc)(int frame, int len);
typedef int (*EntityAnimationFunc)(Entity* entity, int frame, int len);

struct AnimationData
{
    AnimationFunc func;
    int frame;
    int len;
    bool reversed;
};

struct EntityAnimationData
{
    Entity* entity;
    EntityAnimationFunc func;
    int frame;
    int len;
    bool reversed;
};

size_t getAnimationCount();

void processAnimations();

void playAnimation(AnimationFunc func, int len = 0, bool reversed = false);

void playEntityAnimation(Entity* entity, EntityAnimationFunc func, int len = 0, bool reversed = false);

void stopAnimation(AnimationFunc func);

void stopEntityAnimation(EntityAnimationFunc func);

void clearAnimations();

void setGlobalAnimationSpeed(float speed);

float getGlobalAnimationSpeed();
