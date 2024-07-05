#include "vector.h"

namespace GameEngine
{
    Vec2 Vec2::operator+(Vec2 vector)
    {
        return { this->x + vector.x, this->y + vector.y };
    }

    Vec2 Vec2::operator-(Vec2 vector)
    {
        return { this->x - vector.x, this->y - vector.y };
    }

    Vec2 Vec2::operator*(Vec2 vector)
    {
        return { this->x * vector.x, this->y * vector.y };
    }

    Vec2 Vec2::operator/(Vec2 vector)
    {
        return { this->x / vector.x, this->y / vector.y };
    }
}