#pragma once
#include "internal.h"

namespace GameEngine
{
    // Vector2
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

    typedef SDL_Color Color;

    // Round a float value to nearest integer.
    int RountToInt(float input);

    // \returns It returns "On" when true, "Off" when false.
    std::string BoolToString(bool _bool);

    // Calculate a simple linear expression. I recommend using this for transitions in update functions.
    // \param beg The beginning value (the output when frame = 0).
    // \param beg The end value (the output when frame = len).
    // \param len The maximum number of frames.
    // \param frame The actual input of the expression. This should not be larger than `len`.
    float Linear(float beg, float end, float len, float frame);

    // Returns a random number between min and max in int.
    // \param min The minimal output number.
    // \param max The maximum output number.
    int RandomRange(int min, int max);

    // Returns a random number centered at the `center` parameter.
    // \param center The center of the random number.
    // \param difference The maximum offset from the center.
    int RandomCentered(int center, int difference);

    // This is a combination of `RandomRange()` and `RandomCentered()`.
    int RandomEx(int center, int difference, int min, int max);

    bool CheckCollision(Rect a, Rect b);

    class Timer
    {
    public:

        Timer();

        // Start the timer.
        void Start();

        // Returns the duration since the Timer is created or `start` was called. 
        float Get();

    private:
        std::chrono::time_point<std::chrono::steady_clock> startTime, endTime;
        std::chrono::duration<float> duration;
    };
}