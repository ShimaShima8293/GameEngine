#pragma once
#include <chrono>

class Timer
{
public:

    Timer();

    // Start the timer.
    void start();

    // Returns the duration since the Timer is created or `start` was called. 
    float get();

    // Same as `get` but also prints the time.
    float print();

private:
    std::chrono::time_point<std::chrono::steady_clock> startTime, endTime;
    std::chrono::duration<float> duration;
};