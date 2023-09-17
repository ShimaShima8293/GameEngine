#pragma once

#include <vector>
#include <iostream>
#include <math.h>

// Vector2
struct Vec2
{
    float x, y;
};

// Vector3
struct Vec3
{
    float x, y, z;
};

// Vector4
struct Vec4
{
    float x, y, z, w;
};

// Rect
struct Rect
{
    float x, y, w, h;
};

// Round a float value to nearest integer.
int roundToInt(float input);

// \returns It returns "On" when true, "Off" when false.
std::string bool2string(bool _bool);

// Calculate a simple linear expression. I recommend using this for transitions in update functions.
// \param beg The beginning value (the output when frame = 0).
// \param beg The end value (the output when frame = len).
// \param len The maximum number of frames.
// \param frame The actual input of the expression. This should not be larger than `len`.
float linear(float beg, float end, float len, float frame);

// Limits a number between min and max.
// \param target (output) The number to limit
// \param min The minimum
// \param max The maximum
float limit(float input, float min, float max);
void wrap(float& target, float min, float max);
bool between(float target, float min, float max);

// Returns a random number between min and max in int.
// \param min The minimal output number.
// \param max The maximum output number.
int randomRange(int min, int max);

// Returns a random number centered at the `center` parameter.
// \param center The center of the random number.
// \param difference The maximum offset from the center.
int randomCentered(int center, int difference);

// This is a combination of `randomRange()` and `randomCentered()`.
int randomEx(int center, int difference, int min, int max);

bool checkCollision(Rect a, Rect b);