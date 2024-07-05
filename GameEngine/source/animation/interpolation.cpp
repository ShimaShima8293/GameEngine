#include "interpolation.h"

namespace GameEngine
{
    float Linear(float beg, float end, float frame, float len)
    {
        if (frame == 0.0f)
        {
            return beg;
        }
        if (frame == len)
        {
            return end;
        }
        return (((end - beg) / len) * frame) + beg;
    }
}