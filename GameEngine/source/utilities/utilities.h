/*
*  utilities.h
*
*  Useful functions and typedefs.
*  Partially ported from Project18.
*
*/

#pragma once
#include "vector.h"

#include <vector>
#include <string>

namespace GameEngine
{
    float CheckDistance(Vec2 a, Vec2 b);

    float GetAngleBetween(Vec2 a, Vec2 b);

    std::vector<std::string> Split(std::string input, std::string separator);

    Vec2 GetCenterPos(Rect rect);

    void PauseConsole();
}