#pragma once
#include "internal.h"
#include "Window.h"

namespace GameEngine
{
    class Game
    {
    public:
        Game(int flags);
        Window* MakeWindow(std::string title, int width, int height);
        Window* GetWindow(int index);
        int GetWindowCount();

        int SetAntialiasing(bool enableAntialiasing);

        void MainLoop();
        
    private:
        std::vector<Window> windows;

        bool enableAntialiasing = false;
        bool disableDebugging = false;
    };
}