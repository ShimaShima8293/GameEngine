#include "utilities.h"

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

    //void Vec2::operator+=(Vec2 vector)
    //{
    //    *this = *this + vector;
    //}
    //
    //void Vec2::operator-=(Vec2 vector)
    //{
    //    *this = *this + vector;
    //}
    //
    //void Vec2::operator*=(Vec2 vector)
    //{
    //    *this = *this + vector;
    //}
    //
    //void Vec2::operator/=(Vec2 vector)
    //{
    //    *this = *this + vector;
    //}

    int RountToInt(float input)
    {
        return static_cast<int>(std::round(input));
    }

    std::string BoolToString(bool _bool)
    {
        return _bool ? "On" : "Off";
    }

    float Linear(float beg, float end, float len, float frame)
    {
        if (frame == 0)
        {
            return beg;
        }
        if (frame == len)
        {
            return end;
        }
        return (((end - beg) / len) * frame) + beg;
    }

    std::string wstringToString(std::wstring wstr)
    {
        return "";
    }


    int RandomRange(int min, int max)
    {
        return (rand() % (max - min)) + min;
    }

    int RandomCentered(int center, int difference)
    {
        return ((rand() % difference) - (difference / 2)) + center;
    }

    int RandomEx(int center, int difference, int min, int max)
    {
        int tmp = RandomCentered(center, difference);
        if (tmp < min)
        {
            tmp = min;
        }
        if (tmp > max)
        {
            tmp = max;
        }
        return tmp;
    }

    bool CheckCollision(Rect a, Rect b)
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

    Timer::Timer()
    {
        Start();
    }

    void Timer::Start()
    {
        startTime = std::chrono::high_resolution_clock::now();
    }

    float Timer::Get()
    {
        endTime = std::chrono::high_resolution_clock::now();
        duration = endTime - startTime;
        return duration.count();
    }
}