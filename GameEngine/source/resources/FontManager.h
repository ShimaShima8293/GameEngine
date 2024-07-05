#pragma once
#include "Font.h"

#include "internal.h"

#include <vector>

namespace GameEngine
{
    class DebugOutput;

    class FontManager
    {
    public:
        FontManager(std::string path, DebugOutput& output);

        ~FontManager();

        Font& Open(int size, FontAlign align);

        Font& Get(int size, FontAlign align);

        void CloseAll();

    private:
        std::string path;
        std::vector<Font> fonts;
        DebugOutput& output;
    };
}