#include "Sprite.h"
#include "../vars.h"
#include "../events.h"

namespace GameEngine
{
    Sprite::Sprite()
    {
        Free();
    }
    Sprite::~Sprite()
    {
        Free();
    }
    void Sprite::Free()
    {
        if (texture != NULL && !useCommonTexture)
        {
            SDL_DestroyTexture(texture);
            texture = NULL;
        }
        texture = NULL;
        scaleH = 1;
        scaleW = 1;
        visible = true;
        name = "Unnamed";
        red = 255;
        green = 255;
        blue = 255;
        alpha = 255;
        doClip = false;
        clipI = 0;
        clipW = 0;
        rotation = 0.0;
        width = 0, height = 0;
        useColorMod = false;
        useAlphaMod = false;
    }
    bool Sprite::CreateFromImage(std::string path)
    {
        Free();
        SDL_Texture* newTexture = NULL;
        newTexture = IMG_LoadTexture(renderer, path.c_str());
        if (newTexture == NULL)
        {
            PrintErrorGE("Sprite::CreateFromImage: Failed to create image texture. Path: " + path);
            PrintSDLError();
        }
        else
        {
            SDL_QueryTexture(newTexture, NULL, NULL, &width, &height);
            texture = newTexture;
        }

        return newTexture != NULL;
    }
    bool Sprite::CreateFromText(std::string _text, TTF_Font* _font)
    {
        if (_font == NULL)
        {
            PrintErrorGE("Sprite::CreateFromText: Parameter `font` was nullptr.");
            return false;
        }

        if (_text == "")
        {
            PrintErrorGE("Sprite::CreateFromText: Parameter `text` was empty.");
            return false;
        }

        text = _text;
        font = _font;
        textColor = { 255, 255, 255, 255 };
        Free();

        SDL_Surface* textSurface = TTF_RenderUTF8_Blended_Wrapped(font, text.c_str(), textColor, 0);
        if (textSurface == NULL)
        {
            PrintErrorGE("Sprite::CreateFromText: Failed to create surface.");
            PrintSDLError();
            return false;
        }

        SDL_Texture* newTexture = NULL;
        newTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (newTexture == NULL)
        {
            PrintErrorGE("Sprite::CreateFromText: Failed to create texture.");
            PrintSDLError();
            return false;
        }

        width = textSurface->w;
        height = textSurface->h;
        texture = newTexture;

        SDL_FreeSurface(textSurface);


        return newTexture != NULL;
    }
    bool Sprite::CreateFromSurface(SDL_Surface* _surface, bool _free)
    {
        if (_surface == nullptr)
        {
            PrintErrorGE("Sprite::CreateFromSurface: Parameter `surface` was nullptr.");
            return false;
        }

        Free();
        SDL_Texture* newTexture = SDL_CreateTextureFromSurface(renderer, _surface);
        if (newTexture == NULL)
        {
            PrintErrorGE("Sprite::CreateFromSurface: Failed to create texture.");
            PrintSDLError();
            return false;
        }
        else
        {
            width = _surface->w;
            height = _surface->h;
            texture = newTexture;
        }
        if (_free)
        {
            SDL_FreeSurface(_surface);
        }
        return true;
    }
    bool Sprite::CreateSolid(int width, int height, Color color)
    {
        if (width < 1)
        {
            PrintErrorGE("Sprite::CreateSolid: Parameter `width` was smaller than 1.");
            return false;
        }
        if (height < 1)
        {
            PrintErrorGE("Sprite::CreateSolid: Parameter `height` was smaller than 1.");
            return false;
        }

        Free();
        SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, width, height, 32, SDL_PIXELFORMAT_RGBA32);
        if (surface == NULL)
        {
            return false;
        }

        Uint32* pixels = (Uint32*)surface->pixels;

        for (int i = 0; i < width * height; i++)
        {
            pixels[i] = SDL_MapRGBA(surface->format, color.r, color.g, color.b, color.a);
        }

        if (!CreateFromSurface(surface))
        {
            return false;
        }

        return true;
    }
    bool Sprite::CreateGradient(int length, Color color1, Color color2, Orientation orientation)
    {
        if (length < 1)
        {
            PrintErrorGE("Sprite::CreateGradient: Parameter `length` was smaller than 1.");
            return false;
        }

        Free();
        SDL_Surface* surface = orientation == HORIZONTAL ?
            SDL_CreateRGBSurfaceWithFormat(0, length, 1, 32, SDL_PIXELFORMAT_RGBA32) :
            SDL_CreateRGBSurfaceWithFormat(0, 1, length, 32, SDL_PIXELFORMAT_RGBA32);

        Uint32* pixels = (Uint32*)surface->pixels;
        for (int x = 0; x < length; x++)
        {
            pixels[x] = SDL_MapRGBA(
                surface->format,
                RountToInt(Linear((float)color1.r, (float)color2.r, (float)length, (float)x)),
                RountToInt(Linear((float)color1.g, (float)color2.g, (float)length, (float)x)),
                RountToInt(Linear((float)color1.b, (float)color2.b, (float)length, (float)x)),
                RountToInt(Linear((float)color1.a, (float)color2.a, (float)length, (float)x))
            );
        }
        CreateFromSurface(surface);

        return true;
    }
    void Sprite::SetTexture(SDL_Texture* _texture, bool _free)
    {
        if (_texture == nullptr)
        {
            PrintErrorGE("Sprite::SetTexture: Parameter `texture` was nullptr.");
            return;
        }

        Free();
        texture = _texture;
        useCommonTexture = !_free;
        SDL_QueryTexture(_texture, nullptr, nullptr, &width, &height);
    }
    void Sprite::SetParent(SpriteGroup* parent)
    {
        if (parent != nullptr)
        {
            parent->AddChild(this);
        }
        else if (this->parent != nullptr)
        {
            parent->RemoveChild(this);
        }
        this->parent = parent;
    }

    void Sprite::Render(RenderInfo info)
    {
        if (texture == nullptr)
        {
            PrintErrorGE("Sprite::Render: Texture was nullptr.");
            return;
        }

        if (GetVisibility() == false || alpha == 0 || info.visible == false)
        {
            return;
        }

        Uint8 newAlpha = (Uint8)std::round(info.alpha * ((float)alpha / 255.0f));
        if (SDL_SetTextureAlphaMod(texture, newAlpha) != 0)
        {
            PrintErrorGE("Sprite::Render: Failed to set alpha modulation.");
            PrintSDLError();
            return;
        }

        if (useColorMod)
        {
            if (SDL_SetTextureColorMod(texture, red, green, blue) != 0)
            {
                PrintErrorGE("Sprite::Render: Failed to set color modulation.");
                PrintSDLError();
                return;
            }
        }

        float _width = (float)width * scaleW * info.scale.x;
        float _height = (float)height * scaleH * info.scale.y;
        SDL_FRect rect = { position.x + info.position.x, position.y + info.position.y, _width, _height };
        if (doClip)
        {
            SDL_Rect clipRect = { clipW * clipI, 0, clipW, height };
            rect.w = clipRect.w * scaleW * info.scale.x;

            if (SDL_RenderCopyExF(renderer, texture, &clipRect, &rect, rotation + info.rotation, NULL, flip) != 0)
            {
                PrintErrorGE("Sprite::Render: Failed to render.");
                PrintSDLError();
                return;
            }
        }
        else
        {
            if (SDL_RenderCopyExF(renderer, texture, NULL, &rect, rotation + info.rotation, NULL, flip) != 0)
            {
                PrintErrorGE("Sprite::Render: Failed to render.");
                PrintSDLError();
                return;
            }
            if (showBorders)
            {
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
                SDL_RenderDrawRectF(renderer, &rect);
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                SDL_RenderDrawLineF(renderer, GetCX() - 2.0f, GetCY(), GetCX() + 2.0f, GetCY());
                SDL_RenderDrawLineF(renderer, GetCX(), GetCY() - 2.0f, GetCX(), GetCY() + 2.0f);
            }
        }
    }

    void Sprite::SetColor(Uint8 _red, Uint8 _green, Uint8 _blue)
    {
        useColorMod = true;
        red = _red;
        green = _green;
        blue = _blue;
    }

    void Sprite::SetColor(Color _color)
    {
        useColorMod = true;
        red = _color.r;
        green = _color.g;
        blue = _color.b;
        alpha = _color.a;
    }

    void Sprite::SetAlpha(Uint8 _alpha)
    {
        useAlphaMod = true;
        alpha = _alpha;
    }
    Uint8 Sprite::GetAlpha()
    {
        return alpha;
    }
    void Sprite::ClearColor()
    {
        SetColor(255, 255, 255);
        useColorMod = false;
    }
    void Sprite::ClearAlpha()
    {
        SetAlpha(255);
        useAlphaMod = false;
    }
    void Sprite::MoveTo(float speed, float angle)
    {
        ChangePos(speed * std::sin(angle * 3.14f / 180.0f), speed * std::cos(angle * 3.14f / 180.0f));
    }
    float Sprite::GetAngleTowards(float x, float y)
    {
        return 90.0f - atan2(y - GetCY(), x - GetCX()) * (180.0f / 3.14f);
    }
    float Sprite::GetAngleTowards(Vec2 vector)
    {
        return GetAngleTowards(vector.x, vector.y);
    }
    float Sprite::GetTopB()
    {
        return position.y;
    }
    float Sprite::GetBottomB()
    {
        return position.y + GetH();
    }
    float Sprite::GetLeftB()
    {
        return position.x;
    }
    float Sprite::GetRightB()
    {
        return position.x + GetW();
    }
    void Sprite::SetSize(float _w, float _h)
    {
        if (_w <= 0)
        {
            PrintErrorGE("Sprite::SetSize: Parameter `_w` was smaller than 1.");
            return;
        }
        if (_h <= 0)
        {
            PrintErrorGE("Sprite::SetSize: Parameter `_h` was smaller than 1.");
            return;
        }
        // width * scaleW = _w
        scaleW = _w / width;
        scaleH = _h / height;
        // std::cout << "Input: " << _w << " Output: " << (_w / width * width) << std::endl;
    }
    void Sprite::SetSize(Vec2 vector)
    {
        SetSize(vector.x, vector.y);
    }
    void Sprite::ChangeSize(float _w, float _h)
    {
        scaleW += _w;
        scaleH += _h;
    }
    void Sprite::ChangeSize(Vec2 vector)
    {
        ChangeSize(vector.x, vector.y);
    }
    void Sprite::SetScale(float _w, float _h)
    {
        scaleW = _w;
        scaleH = _h;
    }
    void Sprite::SetScale(Vec2 vector)
    {
        SetScale(vector.x, vector.y);
    }
    void Sprite::StretchToWindow()
    {
        SetSize((float)GetGameWidth(), (float)GetGameHeight());
        SetPos(0, 0);
    }
    void Sprite::SetPos(float _x, float _y)
    {
        position.x = _x;
        position.y = _y;
    }
    void Sprite::SetPos(Vec2 vector)
    {
        SetPos(vector.x, vector.y);
    }
    void Sprite::SetX(float _x)
    {
        position.x = _x;
    }
    void Sprite::SetY(float _y)
    {
        position.y = _y;
    }
    void Sprite::SetCPos(float _x, float _y)
    {
        position.x = _x - (GetW() / 2);
        position.y = _y - (GetH() / 2);
    }
    void Sprite::SetCPos(Vec2 vector)
    {
        SetCPos(vector.x, vector.y);
    }
    void Sprite::SetCX(float _x)
    {
        position.x = _x - (GetW() / 2);
    }
    void Sprite::SetCY(float _y)
    {
        position.y = _y - (GetH() / 2);
    }
    void Sprite::SetRect(Rect rect)
    {
        SetPos(rect.x, rect.y);
        SetSize(rect.w, rect.h);
    }
    Rect Sprite::GetRect()
    {
        return { GetX(), GetY(), GetW(), GetH() };
    }
    void Sprite::SetPosCentered()
    {
        SetPos(GetWindowCenterX(), GetWindowCenterY());
    }
    void Sprite::ChangePos(float _x, float _y)
    {
        position.x += _x;
        position.y += _y;
    }
    void Sprite::ChangePos(Vec2 vector)
    {
        ChangePos(vector.x, vector.y);
    }
    Vec2 Sprite::GetPos()
    {
        return position;
    }
    Vec2 Sprite::GetCPos()
    {
        return { position.x + (GetW() / 2), position.y + (GetH() / 2) };
    }
    float Sprite::GetX()
    {
        return position.x;
    }
    float Sprite::GetY()
    {
        return position.y;
    }
    float Sprite::GetCX()
    {
        return position.x + (GetW() / 2);
    }
    float Sprite::GetCY()
    {
        return position.y + (GetH() / 2);
    }
    float Sprite::GetW()
    {
        if (doClip)
        {
            return (float)clipW * scaleW;
        }
        return (float)(width)*scaleW;
    }
    float Sprite::GetH()
    {
        return (float)(height)*scaleH;
    }

    int Sprite::GetTextureW()
    {
        return width;
    }
    int Sprite::GetTextureH()
    {
        return height;
    }
    float Sprite::GetTextureRatio()
    {
        return (float)width / (float)height;
    }
    void Sprite::SetClipPos(int _clipW, int _clipI = 0)
    {
        clipW = _clipW;
        clipI = _clipI;
    }
    void Sprite::ClipNext()
    {
        clipI++;
        if (clipI * clipW >= width)
        {
            clipI = 0;
        }
    }
    float Sprite::GetWindowCenterX()
    {
        return GetGameWidth() / 2.0f - GetW() / 2.0f;
    }
    float Sprite::GetWindowCenterY()
    {
        return GetGameHeight() / 2.0f - GetH() / 2.0f;
    }
    std::string Sprite::GetName()
    {
        return name;
    }
    void Sprite::SetName(std::string _name)
    {
        name = _name;
    }
    float Sprite::GetScaleW()
    {
        return scaleW;
    }
    float Sprite::GetScaleH()
    {
        return scaleH;
    }
    Color Sprite::GetColor()
    {
        return { red, green, blue, alpha };
    }
    // Use this if you are only changing the text. Its lighter than `CreateFromText`
    void Sprite::SetText(std::string _text)
    {
        if (text != _text)
        {
            CreateFromText(_text, font);
            text = _text;
        }
    }

    // Rotation
    void Sprite::SetRotation(float _rotation)
    {
        rotation = _rotation;
    }
    void Sprite::ChangeRotation(float _rotation)
    {
        SetRotation(GetRotation() + _rotation);
    }
    float Sprite::GetRotation()
    {
        return rotation;
    }

    void Sprite::SetVisibility(bool _visible)
    {
        visible = _visible;
    }

    bool Sprite::GetVisibility()
    {
        return visible;
    }

    void Sprite::SetClip(bool _doClip)
    {
        doClip = _doClip;
    }

    bool Sprite::GetClip()
    {
        return doClip;
    }

    void Sprite::SetFlip(SDL_RendererFlip _flip)
    {
        flip = _flip;
    }

    SDL_RendererFlip Sprite::GetFlip()
    {
        return flip;
    }

    SDL_Texture* Sprite::GetTexture()
    {
        return texture;
    }
}