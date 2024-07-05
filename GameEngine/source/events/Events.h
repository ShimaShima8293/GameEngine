#pragma once

#include "internal.h"

#include <vector>
#include <SDL_events.h>

namespace GameEngine
{
    class DebugOutput;

    class Events
    {
    public:
        Events(DebugOutput& output);

        SDL_Event GetAt(int index);

        int GetSize();

    private:
        std::vector<SDL_Event> events;
        DebugOutput& output;
    };
}