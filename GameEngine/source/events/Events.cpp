#include "Events.h"

#include "debugging/DebugOutput.h"

namespace GameEngine
{
    Events::Events(DebugOutput& output) :
        events(),
        output(output)
    {
    }

    SDL_Event Events::GetAt(int index)
    {
        if (index >= this->GetSize())
        {
            output.ErrorGE("Events::GetAt: Parameter `index` was too large.");
            return {};
        }

        return events[index];
    }

    int Events::GetSize()
    {
        return events.size();
    }
}