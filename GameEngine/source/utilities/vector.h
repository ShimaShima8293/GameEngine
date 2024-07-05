#pragma once
#include "internal.h"

namespace GameEngine
{
    struct Vec2
    {
        float x, y;
        Vec2 operator+(Vec2 vector);
        Vec2 operator-(Vec2 vector);
        Vec2 operator*(Vec2 vector);
        Vec2 operator/(Vec2 vector);
        //void operator+=(Vec2 vector);
        //void operator-=(Vec2 vector);
        //void operator*=(Vec2 vector);
        //void operator/=(Vec2 vector);
    };

    struct Vec3
    {
        float x, y, z;
    };

    struct Vec4
    {
        float x, y, z, w;
    };

    struct Rect
    {
        float x, y, w, h;
    };

    struct Color
    {
        unsigned char r, g, b, a;
    };
}