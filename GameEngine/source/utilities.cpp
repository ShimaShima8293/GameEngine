#include "utilities.h"

Vec2 Vec2::operator+(Vec2 vector)
{
    return {this->x + vector.x, this->y + vector.y};
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

int roundToInt(float input)
{
    return static_cast<int>(std::round(input));
}

std::string bool2string(bool _bool)
{
    return _bool ? "On" : "Off";
}

float linear(float beg, float end, float len, float frame)
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

float limit(float input, float min, float max)
{
    if (input < min)
    {
        return min;
    }
    if (input > max)
    {
        return max;
    }
    return input;
}

void wrap(float& target, float min, float max)
{
    if (target < min)
    {
        target = max;
    }
    if (target > max)
    {
        target = min;
    }
}

bool between(float target, float min, float max)
{
    if (target < min)
    {
        return false;
    }
    if (target > max)
    {
        return false;
    }
    return true;

}

std::string wstringToString(std::wstring wstr)
{
    return "";
}


int randomRange(int min, int max)
{
    return (rand() % (max - min)) + min;
}

int randomCentered(int center, int difference)
{
    return ((rand() % difference) - (difference / 2)) + center;
}

int randomEx(int center, int difference, int min, int max)
{
    int tmp = randomCentered(center, difference);
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

bool checkCollision(Rect a, Rect b)
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
    start();
}

void Timer::start()
{
    startTime = std::chrono::high_resolution_clock::now();
}

float Timer::get()
{
    endTime = std::chrono::high_resolution_clock::now();
    duration = endTime - startTime;
    return duration.count();
}

float Timer::print()
{
    float time = get();
    printInfo("Timer::print: current time: " + std::to_string(time));
    return time;
}