#include "Timer.h"
#include "macros.h"

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
    printInfo("Timer::print current time: " << time);
    return time;
}