#include <random>
#include <iostream>
#include <math.h>
#include "utilities.h"
#include <vector>

int roundToInt(float input)
{
    return static_cast<int>(std::round(input));
}

std::string bool2string(bool _bool)
{
    return _bool ? "On" : "Off";
}

int linear(int beg, int end, int len, int frame)
{
    return roundToInt(linear((float)beg, (float)end, (float)len, (float)frame));
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