#include "FontManager.h"
#include "debugging/DebugOutput.h"

namespace GameEngine
{
    FontManager::FontManager(std::string path, DebugOutput& output) :
        path(path),
        fonts(),
        output(output)
    {
    }

    FontManager::~FontManager()
    {
    }

    Font& FontManager::Open(int size, FontAlign align)
    {
        return fonts.emplace_back(path, size, align, output);
    }

    Font& FontManager::Get(int size, FontAlign align)
    {
        for (Font& font : fonts)
        {
            if (font.GetSize() == size && font.GetAlign() == align)
            {
                return font;
            }
        }

        return Open(size, align);
    }

    void FontManager::CloseAll()
    {
        fonts.clear();
    }
}