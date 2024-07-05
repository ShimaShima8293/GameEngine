#pragma once
#include "internal.h"

#include <SDL_ttf.h>

#include <string>

namespace GameEngine
{
    class DebugOutput;

    enum FontAlign
    {
        FONT_ALIGN_LEFT,
        FONT_ALIGN_CENTER,
        FONT_ALIGN_RIGHT
    };

    class Font
    {
    public:
        Font(std::string path, int size, FontAlign align, DebugOutput& output);

        TTF_Font* GetSDLRenderer();

        int GetSize() const;

        FontAlign GetAlign() const;

    private:
        TTF_Font* font;
        int size;
        FontAlign align;
        DebugOutput& output;
    };
}