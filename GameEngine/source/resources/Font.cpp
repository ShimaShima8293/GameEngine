#include "Font.h"
#include "debugging/DebugOutput.h"

namespace GameEngine
{
    Font::Font(std::string path, int size, FontAlign align, DebugOutput& output) :
        font(nullptr),
        size(size),
        align(align),
        output(output)
    {
        font = TTF_OpenFont(path.c_str(), size);
        if (!font)
        {
            output.Error("Font::Font: Failed to load font at " + path);
            return;
        }
        TTF_SetFontWrappedAlign(font, align);
    }

    TTF_Font* Font::GetSDLRenderer()
    {
        return font;
    }

    int Font::GetSize() const
    {
        return size;
    }

    FontAlign Font::GetAlign() const
    {
        return align;
    }
}