#pragma once

#include "events/Events.h"

#include "internal.h"

namespace GameEngine
{
    class Input
    {
    public:
        Input();

        void HandleEvents(Events event);
    };
}