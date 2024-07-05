/*
*  collision.h
*
*  Functions for detecting and resolving collisions.
*
*/

#pragma once
#include "internal.h"

namespace GameEngine
{
    struct Rect;

    enum Direction
    {
        NONE,
        LEFT,
        RIGHT,
        UP,
        DOWN
    };

    struct CollisionData
    {
        Direction direction = NONE;
        float distance = 0.0f;
    };

    bool CheckCollision(Rect& a, Rect& b);

    CollisionData CheckCollisionWithDirection(Rect& a, Rect& b);
}