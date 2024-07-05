#include "collision.h"

#include "utilities/utilities.h"

namespace GameEngine
{
    bool CheckCollision(Rect& a, Rect& b)
    {
        if (a.y + a.h <= b.y)
        {
            return false;
        }
        if (a.y >= b.y + b.h)
        {
            return false;
        }
        if (a.x + a.w <= b.x)
        {
            return false;
        }
        if (a.x >= b.x + b.w)
        {
            return false;
        }
        return true;
    }

    CollisionData CheckCollisionWithDirection(Rect& a, Rect& b)
    {
        if (CheckCollision(a, b))
        {
            float distance = FLT_MAX;
            Direction direction = NONE;

            // TarGet going left
            if (a.x < b.x + b.w)
            {
                float currentDistance = abs(b.x + b.w - a.x);
                if (currentDistance < distance)
                {
                    distance = currentDistance;
                    direction = LEFT;
                }
            }

            // TarGet going right
            if (a.x + a.w > b.x)
            {
                float currentDistance = abs(a.x + a.w - b.x);
                if (currentDistance < distance)
                {
                    distance = currentDistance;
                    direction = RIGHT;
                }
            }

            // TarGet going up
            if (a.y < b.y + b.h)
            {
                float currentDistance = abs(b.y + b.h - a.y);
                if (currentDistance < distance)
                {
                    distance = currentDistance;
                    direction = UP;
                }
            }

            // TarGet going down
            if (a.y + a.h > b.y)
            {
                float currentDistance = abs(a.y + a.h - b.y);
                if (currentDistance < distance)
                {
                    distance = currentDistance;
                    direction = DOWN;
                }
            }
            return { direction, distance };
        }
        return { NONE, 0.0f };
    }
}