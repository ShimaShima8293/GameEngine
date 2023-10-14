#include "sprite.h"
#include "vars.h"
#include "events.h"

using namespace GameEngine;

Sprite::Sprite()
{
    free();
}
Sprite::~Sprite()
{
    free();
}
void Sprite::free()
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
bool Sprite::createFromImage(std::string path)
{
    free();
    SDL_Texture* newTexture = NULL;
    newTexture = IMG_LoadTexture(renderer, path.c_str());
    if (newTexture == NULL)
    {
        printError("Sprite::createFromImage: Failed to create image texture. SDL Error: " << SDL_GetError());
    }
    else
    {
        SDL_QueryTexture(newTexture, NULL, NULL, &width, &height);
        texture = newTexture;
    }

    return newTexture != NULL;
}
bool Sprite::createFromText(std::string _text, TTF_Font* _font)
{
    if (_font == NULL)
    {
        printError("Sprite::createFromText: font was nullptr.");
        return false;
    }

    if (_text == "")
    {
        printError("Sprite::createFromText: text was empty.");
        return false;
    }

    text = _text;
    font = _font;
    textColor = { 255, 255, 255, 255 };
    free();

    SDL_Surface* textSurface = TTF_RenderUTF8_Blended_Wrapped(font, text.c_str(), textColor, 0);
    if (textSurface == NULL)
    {
        printError("Sprite::createFromText: Failed to create surface. SDL_TTF Error: " << TTF_GetError());
        return false;
    }

    SDL_Texture* newTexture = NULL;
    newTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (newTexture == NULL)
    {
        printError("Sprite::createFromText: Failed to create texture. SDL Error: " << SDL_GetError());
        return false;
    }

    width = textSurface->w;
    height = textSurface->h;
    texture = newTexture;

    SDL_FreeSurface(textSurface);


    return newTexture != NULL;
}
bool Sprite::createFromSurface(SDL_Surface* _surface, bool _free)
{
    if (_surface == nullptr)
    {
        printError("Sprite::createFromSurface: Parameter surface was nullptr.");
        return false;
    }

    free();
    SDL_Texture* newTexture = SDL_CreateTextureFromSurface(renderer, _surface);
    if (newTexture == NULL)
    {
        printError("Sprite::createFromSurface: Failed to create texture. SDL Error: " << SDL_GetError());
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
bool Sprite::createSolid(int width, int height, Color color)
{
    if (width < 1 || height < 1)
    {
        printError("Sprite::createSolid: width or height cannot be smaller than 1.");
        return false;
    }

    free();
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

    if (!createFromSurface(surface))
    {
        return false;
    }

    return true;
}
bool Sprite::createGradient(int length, Color color1, Color color2, Orientation orientation)
{
    if (length < 1)
    {
        printError("Sprite::createGradient: length cannot be smaller than 1.");
        return false;
    }

    free();
    SDL_Surface* surface = orientation == HORIZONTAL ?
        SDL_CreateRGBSurfaceWithFormat(0, length, 1, 32, SDL_PIXELFORMAT_RGBA32) :
        SDL_CreateRGBSurfaceWithFormat(0, 1, length, 32, SDL_PIXELFORMAT_RGBA32);

    Uint32* pixels = (Uint32*)surface->pixels;
    for (int x = 0; x < length; x++)
    {
        pixels[x] = SDL_MapRGBA(
            surface->format,
            roundToInt(linear((float)color1.r, (float)color2.r, (float)length, (float)x)),
            roundToInt(linear((float)color1.g, (float)color2.g, (float)length, (float)x)),
            roundToInt(linear((float)color1.b, (float)color2.b, (float)length, (float)x)),
            roundToInt(linear((float)color1.a, (float)color2.a, (float)length, (float)x))
        );
    }
    createFromSurface(surface);

    return false;
}
void Sprite::setTexture(SDL_Texture* _texture, bool _free)
{
    if (_texture == nullptr)
    {
        printError("Sprite::setTexture: texture was nullptr.");
        return;
    }

    free();
    texture = _texture;
    useCommonTexture = !_free;
    SDL_QueryTexture(_texture, nullptr, nullptr, &width, &height);
}
void Sprite::render()
{
    if (getVisibility() == false || alpha == 0)
    {
        return;
    }

    if (useAlphaMod)
    {
        if (SDL_SetTextureAlphaMod(texture, alpha) != 0)
        {
            printError("Sprite::render: Failed to set alpha modulation. SDL Error: " << SDL_GetError());
        }
    }
    if (useColorMod)
    {
        if (SDL_SetTextureColorMod(texture, red, green, blue) != 0)
        {
            printError("Sprite::render: Failed to set color modulation. SDL Error: " << SDL_GetError());
        }
    }

    float _width = (float)width * scaleW;
    float _height = (float)height * scaleH;
    SDL_FRect rect = { position.x, position.y, _width, _height };
    if (doClip)
    {
        SDL_Rect clipRect = { clipW * clipI, 0, clipW, height };
        rect.w = clipRect.w * scaleW;

        if (SDL_RenderCopyExF(renderer, texture, &clipRect, &rect, rotation, NULL, flip) != 0)
        {
            printError("Sprite::render: Failed to render. SDL Error: " << SDL_GetError());
        }
    }
    else
    {
        if (SDL_RenderCopyExF(renderer, texture, NULL, &rect, rotation, NULL, flip) != 0)
        {
            printError("Sprite::render: Failed to render. SDL Error: " << SDL_GetError());
        }
    }
    if (showBorders)
    {
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderDrawRectF(renderer, &rect);
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderDrawLineF(renderer, getCX() - 2.0f, getCY(), getCX() + 2.0f, getCY());
        SDL_RenderDrawLineF(renderer, getCX(), getCY() - 2.0f, getCX(), getCY() + 2.0f);
    }
}

void Sprite::setColor(Uint8 _red, Uint8 _green, Uint8 _blue)
{
    useColorMod = true;
    red = _red;
    green = _green;
    blue = _blue;
}

void Sprite::setColor(Color _color)
{
    useColorMod = true;
    red = _color.r;
    green = _color.g;
    blue = _color.b;
    if (_color.a)
    {
        alpha = _color.a;
    }
}

void Sprite::setAlpha(Uint8 _alpha)
{
    useAlphaMod = true;
    alpha = _alpha;
}
void Sprite::clearColor()
{
    setColor(255, 255, 255);
    useColorMod = false;
}
void Sprite::clearAlpha()
{
    setAlpha(255);
    useAlphaMod = false;
}
void Sprite::moveTo(float speed, float angle)
{
    changePos(speed * std::sin(angle * 3.14f / 180.0f), speed * std::cos(angle * 3.14f / 180.0f));
}
float Sprite::getAngleTowards(float x, float y)
{
    return 90.0f - atan2(y - getCY(), x - getCX()) * (180.0f / 3.14f);
}
float Sprite::getAngleTowards(Vec2 vector)
{
    return getAngleTowards(vector.x, vector.y);
}
float Sprite::getTopB()
{
    return position.y;
}
float Sprite::getBottomB()
{
    return position.y + getH();
}
float Sprite::getLeftB()
{
    return position.x;
}
float Sprite::getRightB()
{
    return position.x + getW();
}
void Sprite::setSize(float _w, float _h)
{
    if (_w < 0 || _h < 0)
    {
        printError("Sprite::setSize: width or height was smaller than 0.");
        return;
    }
    // width * scaleW = _w
    scaleW = _w / width;
    scaleH = _h / height;
    // std::cout << "Input: " << _w << " Output: " << (_w / width * width) << std::endl;
}
void Sprite::setSize(Vec2 vector)
{
    setSize(vector.x, vector.y);
}
void Sprite::changeSize(float _w, float _h)
{
    scaleW += _w;
    scaleH += _h;
}
void Sprite::changeSize(Vec2 vector)
{
    changeSize(vector.x, vector.y);
}
void Sprite::setScale(float _w, float _h)
{
    scaleW = _w;
    scaleH = _h;
}
void Sprite::setScale(Vec2 vector)
{
    setScale(vector.x, vector.y);
}
void Sprite::stretchToWindow()
{
    setSize((float)getGameWidth(), (float)getGameHeight());
    setPos(0, 0);
}
void Sprite::fitToWindow()
{
    if (getGameHeight() / getGameWidth() > getH() / getW())
    {

    }
}
void Sprite::setPos(float _x, float _y)
{
    position.x = _x;
    position.y = _y;
}
void Sprite::setPos(Vec2 vector)
{
    setPos(vector.x, vector.y);
}
void Sprite::setX(float _x)
{
    position.x = _x;
}
void Sprite::setY(float _y)
{
    position.y = _y;
}
void Sprite::setCPos(float _x, float _y)
{
    position.x = _x - (getW() / 2);
    position.y = _y - (getH() / 2);
}
void Sprite::setCPos(Vec2 vector)
{
    setCPos(vector.x, vector.y);
}
void Sprite::setCX(float _x)
{
    position.x = _x - (getW() / 2);
}
void Sprite::setCY(float _y)
{
    position.y = _y - (getH() / 2);
}
void Sprite::setRect(Rect rect)
{
    setPos(rect.x, rect.y);
    setSize(rect.w, rect.h);
}
Rect Sprite::getRect()
{
    return { getX(), getY(), getW(), getH() };
}
void Sprite::setPosCentered()
{
    setPos(getWindowCenterX(), getWindowCenterY());
}
void Sprite::changePos(float _x, float _y)
{
    position.x += _x;
    position.y += _y;
}
void Sprite::changePos(Vec2 vector)
{
    changePos(vector.x, vector.y);
}
Vec2 Sprite::getPos()
{
    return position;
}
Vec2 Sprite::getCPos()
{
    return { position.x + (getW() / 2), position.y + (getH() / 2) };
}
float Sprite::getX()
{
    return position.x;
}
float Sprite::getY()
{
    return position.y;
}
float Sprite::getCX()
{
    return position.x + (getW() / 2);
}
float Sprite::getCY()
{
    return position.y + (getH() / 2);
}
float Sprite::getW()
{
    if (doClip)
    {
        return (float)clipW * scaleW;
    }
    return (float)(width)*scaleW;
}
float Sprite::getH()
{
    return (float)(height)*scaleH;
}

int Sprite::getTextureW()
{
    return width;
}
int Sprite::getTextureH()
{
    return height;
}
float Sprite::getTextureRatio()
{
    return (float)width / (float)height;
}
void Sprite::setClipPos(int _clipW, int _clipI = 0)
{
    clipW = _clipW;
    clipI = _clipI;
}
void Sprite::clipNext()
{
    clipI++;
    if (clipI * clipW >= width)
    {
        clipI = 0;
    }
}
float Sprite::getWindowCenterX()
{
    return getGameWidth() / 2.0f - getW() / 2.0f;
}
float Sprite::getWindowCenterY()
{
    return getGameHeight() / 2.0f - getH() / 2.0f;
}
std::string Sprite::getName()
{
    return name;
}
void Sprite::setName(std::string _name)
{
    name = _name;
}
float Sprite::getScaleW()
{
    return scaleW;
}
float Sprite::getScaleH()
{
    return scaleH;
}
Color Sprite::getColor()
{
    return { red, green, blue, alpha };
}
// Use this if you are only changing the text. Its lighter than `createFromText`
void Sprite::setText(std::string _text)
{
    if (text != _text)
    {
        createFromText(_text, font);
        text = _text;
    }
}

// Rotation
void Sprite::setRotation(float _rotation)
{
    rotation = _rotation;
}
void Sprite::changeRotation(float _rotation)
{
    setRotation(getRotation() + _rotation);
}
float Sprite::getRotation()
{
    return rotation;
}

void Sprite::setVisibility(bool _visible)
{
    visible = _visible;
}

bool Sprite::getVisibility()
{
    return visible;
}

void Sprite::setClip(bool _doClip)
{
    doClip = _doClip;
}

bool Sprite::getClip()
{
    return doClip;
}

void Sprite::setFlip(SDL_RendererFlip _flip)
{
    flip = _flip;
}

SDL_RendererFlip Sprite::getFlip()
{
    return flip;
}
