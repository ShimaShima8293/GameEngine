#include <iostream>
#include "Entity.h"
#include "vars.h"
#include "events.h"
#include <math.h>
#include PATH_SDL
#include PATH_SDL_IMAGE
#include PATH_SDL_TTF
#include PATH_SDL_MIXER

using namespace GameEngine;

Entity::Entity()
{
    free();
}
Entity::~Entity()
{
    free();
}
void Entity::free()
{
    if (texture != NULL)
    {
        SDL_DestroyTexture(texture);
        texture = NULL;
    }
    texture = NULL;
    scaleH = 1;
    scaleW = 1;
    visible = true;
    name = "Unnamed";
    type = ENTITY_NULL;
    red = 255;
    green = 255;
    blue = 255;
    alpha = 255;
}
bool Entity::createFromImage(std::string path)
{
    free();
    SDL_Texture* newTexture = NULL;
    newTexture = IMG_LoadTexture(renderer, path.c_str());
    if (newTexture == NULL)
    {
        printError("Entity::createFromImage: Failed to create image texture. SDL Error: " << SDL_GetError());
    }
    else
    {
        SDL_QueryTexture(newTexture, NULL, NULL, &width, &height);
        texture = newTexture;
        type = ENTITY_IMAGE;
    }

    return newTexture != NULL;
}
bool Entity::createFromText(std::string _text, TTF_Font* _font)
{
    if (_font == NULL)
    {
        printError("Entity::createFromText: font was nullptr.");
        return false;
    }

    if (_text == "")
    {
        printError("Entity::createFromText: text was empty.");
        return false;
    }

    text = _text;
    font = _font;
    textColor = { 255, 255, 255, 255 };
    free();

    SDL_Surface* textSurface = TTF_RenderUTF8_Blended_Wrapped(font, text.c_str(), textColor, 0);
    if (textSurface == NULL)
    {
        printError("Entity::createFromText: Failed to create surface. SDL_TTF Error: " << TTF_GetError());
        return false;
    }

    SDL_Texture* newTexture = NULL;
    newTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (newTexture == NULL)
    {
        printError("Entity::createFromText: Failed to create texture. SDL Error: " << SDL_GetError());
        return false;
    }

    width = textSurface->w;
    height = textSurface->h;
    texture = newTexture;
    type = ENTITY_TEXT;

    SDL_FreeSurface(textSurface);


    return newTexture != NULL;
}
bool Entity::createFromSurface(SDL_Surface* _surface, bool _free)
{
    if (_surface == nullptr)
    {
        printError("Entity::createFromSurface: Parameter surface was nullptr.");
        return false;
    }

    free();
    SDL_Texture* newTexture = SDL_CreateTextureFromSurface(renderer, _surface);
    if (newTexture == NULL)
    {
        printError("Entity::createFromSurface: Failed to create texture. SDL Error: " << SDL_GetError());
        return false;
    }
    else
    {
        width = _surface->w;
        height = _surface->h;
        texture = newTexture;
        type = ENTITY_CUSTOM;
    }
    if (_free)
    {
        SDL_FreeSurface(_surface);
    }
    return true;
}
bool Entity::createSolid(int width, int height, SDL_Color color)
{
    if (width < 1 || height < 1)
    {
        printError("Entity::createSolid: width or height cannot be smaller than 1.");
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
bool Entity::createGradient(int length, SDL_Color color1, SDL_Color color2, Orientation orientation)
{
    if (length < 1)
    {
        printError("Entity::createGradient: length cannot be smaller than 1.");
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
            roundToInt(linear(color1.r, color2.r, length, x)),
            roundToInt(linear(color1.g, color2.g, length, x)),
            roundToInt(linear(color1.b, color2.b, length, x)),
            roundToInt(linear(color1.a, color2.a, length, x))
        );
    }
    createFromSurface(surface);

    return false;
}
void Entity::setTexture(SDL_Texture* _texture)
{
    free();
    texture = _texture;
}
void Entity::render()
{
    if (getVisibility() == false)
    {
        return;
    }

    if (useAlphaMod)
    {
        if (SDL_SetTextureAlphaMod(texture, alpha) != 0)
        {
            printError("Entity::render: Failed to set alpha modulation. SDL Error: " << SDL_GetError());
        }
    }
    if (useColorMod)
    {
        if (SDL_SetTextureColorMod(texture, red, green, blue) != 0)
        {
            printError("Entity::render: Failed to set color modulation. SDL Error: " << SDL_GetError());
        }
    }

    int _width = static_cast<int>(std::round((double)width * scaleW));
    int _height = static_cast<int>(std::round((double)height * scaleH));
    rect = { position.x, position.y, _width, _height };
    if (doClip)
    {
        clipRect = { clipW * clipI, 0, clipW, height };
        rect.w = (int)(clipRect.w * scaleW);

        if (SDL_RenderCopyEx(renderer, texture, &clipRect, &rect, rotation, NULL, SDL_FLIP_NONE) != 0)
        {
            printError("Entity::render: Failed to render. SDL Error: " << SDL_GetError());
        }
    }
    else
    {
        if (SDL_RenderCopyEx(renderer, texture, NULL, &rect, rotation, NULL, SDL_FLIP_NONE) != 0)
        {
            printError("Entity::render: Failed to render. SDL Error: " << SDL_GetError());
        }
    }
}

void Entity::setColor(Uint8 _red, Uint8 _green, Uint8 _blue)
{
    useColorMod = true;
    red = _red;
    green = _green;
    blue = _blue;
}

void Entity::setColor(SDL_Color _color)
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

void Entity::setAlpha(Uint8 _alpha)
{
    useAlphaMod = true;
    alpha = _alpha;
}
void Entity::clearColor()
{
    setColor(255, 255, 255);
    useColorMod = false;
}
void Entity::clearAlpha()
{
    setAlpha(255);
    useAlphaMod = false;
}
void Entity::moveTo(int speed, int angle)
{
    changePos((int)(std::round(speed * std::sin(angle * 3.14 / 180))), (int)(std::round(speed * std::cos(angle * 3.14 / 180))));
}
int Entity::getTopB()
{
    return position.y;
}
int Entity::getBottomB()
{
    return position.y + getH();
}
int Entity::getLeftB()
{
    return position.x;
}
int Entity::getRightB()
{
    return position.x + getW();
}
void Entity::setSize(double _w, double _h)
{
    if (_w < 0 || _h < 0)
    {
        printError("Entity::setSize: width or height was smaller than 0.");
        return;
    }
    // width * scaleW = _w
    scaleW = _w / width;
    scaleH = _h / height;
    // std::cout << "Input: " << _w << " Output: " << (_w / width * width) << std::endl;
}
void Entity::setSize(Vec2 vector)
{
    setSize(vector.x, vector.y);
}
void Entity::changeSize(double _w, double _h)
{
    scaleW += _w;
    scaleH += _h;
}
void Entity::changeSize(Vec2 vector)
{
    changeSize(vector.x, vector.y);
}
void Entity::setScale(double _w, double _h)
{
    scaleW = _w;
    scaleH = _h;
}
void Entity::setScale(Vec2 vector)
{
    setScale(vector.x, vector.y);
}
void Entity::stretchToWindow()
{
    setSize(getGameWidth(), getGameHeight());
    setPos(0, 0);
}
void Entity::fitToWindow()
{
    if (getGameHeight() / getGameWidth() > getH() / getW())
    {

    }
}
void Entity::setPos(int _x, int _y)
{
    position.x = _x;
    position.y = _y;
}
void Entity::setPos(Vec2 vector)
{
    setPos((int)vector.x, (int)vector.y);
}
void Entity::setPosCentered()
{
    setPos(getWindowCenterX(), getWindowCenterY());
}
void Entity::changePos(int _x, int _y)
{
    position.x += _x;
    position.y += _y;
}
void Entity::changePos(Vec2 vector)
{
    changePos((int)vector.x, (int)vector.y);
}
int Entity::getX()
{
    return position.x;
}
int Entity::getY()
{
    return position.y;
}
int Entity::getW()
{
    return static_cast<int>(static_cast<double>(width) * scaleW);
}
int Entity::getH()
{
    return static_cast<int>(static_cast<double>(height) * scaleH);
}

int Entity::getTextureW()
{
    return width;
}
int Entity::getTextureH()
{
    return height;
}
float Entity::getTextureRatio()
{
    return (float)width / (float)height;
}
void Entity::setClipPos(int _clipW, int _clipI = 0)
{
    clipW = _clipW;
    clipI = _clipI;
}
void Entity::clipNext()
{
    clipI++;
}
int Entity::getWindowCenterX()
{
    return getGameWidth() / 2 - getW() / 2;
}
int Entity::getWindowCenterY()
{
    return getGameHeight() / 2 - getH() / 2;
}
std::string Entity::getName()
{
    return name;
}
void Entity::setName(std::string _name)
{
    name = _name;
}
double Entity::getScaleW()
{
    return scaleW;
}
double Entity::getScaleH()
{
    return scaleH;
}
SDL_Color Entity::getColor()
{
    return { red, green, blue, alpha };
}
// Use this if you are only changing the text. Its lighter than `createFromText`
void Entity::setText(std::string _text)
{
    if (text != _text)
    {
        createFromText(_text, font);
        text = _text;
    }
}

// Rotation
void Entity::setRotation(double _rotation)
{
    rotation = _rotation;
}
void Entity::changeRotation(double _rotation)
{
    setRotation(getRotation() + _rotation);
}
double Entity::getRotation()
{
    return rotation;
}

void Entity::setVisibility(bool _visible)
{
    visible = _visible;
}

bool Entity::getVisibility()
{
    return visible;
}

void Entity::setClip(bool _doClip)
{
    doClip = _doClip;
}

bool Entity::getClip()
{
    return doClip;
}
