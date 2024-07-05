#pragma once
#include "Sprite.h"

#include <memory>

namespace GameEngine
{
    class Font;

    class TextSprite /*: public Sprite*/
    {
    public:
        //TextSprite(std::string text, std::shared_ptr<Font> font);

    private:
        std::string text;
        std::shared_ptr<Font> font;
    };
}