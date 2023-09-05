#include <iostream>
#include "Entity.h"
#include "vars.h"
#include "events.h"
#include <math.h>
#include <cmath>
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
            roundToInt(linear((float)color1.r, (float)color2.r, (float)length, (float)x)),
            roundToInt(linear((float)color1.g, (float)color2.g, (float)length, (float)x)),
            roundToInt(linear((float)color1.b, (float)color2.b, (float)length, (float)x)),
            roundToInt(linear((float)color1.a, (float)color2.a, (float)length, (float)x))
        );
    }
    createFromSurface(surface);

    return false;
}
void Entity::setTexture(SDL_Texture* _texture, bool _free)
{
    if (_texture == nullptr)
    {
        printError("Entity::setTexture: texture was nullptr.");
        return;
    }

    free();
    texture = _texture;
    useCommonTexture = !_free;
    SDL_QueryTexture(_texture, nullptr, nullptr, &width, &height);
}
void Entity::render()
{
    if (getVisibility() == false || alpha == 0)
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

    float _width = (float)width * scaleW;
    float _height = (float)height * scaleH;
    SDL_FRect rect = { position.x, position.y, _width, _height };
    if (doClip)
    {
        SDL_Rect clipRect = { clipW * clipI, 0, clipW, height };
        rect.w = clipRect.w * scaleW;

        if (SDL_RenderCopyExF(renderer, texture, &clipRect, &rect, rotation, NULL, flip) != 0)
        {
            printError("Entity::render: Failed to render. SDL Error: " << SDL_GetError());
        }
    }
    else
    {
        if (SDL_RenderCopyExF(renderer, texture, NULL, &rect, rotation, NULL, flip) != 0)
        {
            printError("Entity::render: Failed to render. SDL Error: " << SDL_GetError());
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
void Entity::moveTo(float speed, float angle)
{
    changePos(speed * std::sin(angle * 3.14f / 180.0f), speed * std::cos(angle * 3.14f / 180.0f));
}
float Entity::getAngleTowards(float x, float y)
{
    return 90.0f - atan2(y - getCY(), x - getCX()) * (180.0f / 3.14f);
}
float Entity::getAngleTowards(Vec2 vector)
{
    return getAngleTowards(vector.x, vector.y);
}
float Entity::getTopB()
{
    return position.y;
}
float Entity::getBottomB()
{
    return position.y + getH();
}
float Entity::getLeftB()
{
    return position.x;
}
float Entity::getRightB()
{
    return position.x + getW();
}
void Entity::setSize(float _w, float _h)
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
void Entity::changeSize(float _w, float _h)
{
    scaleW += _w;
    scaleH += _h;
}
void Entity::changeSize(Vec2 vector)
{
    changeSize(vector.x, vector.y);
}
void Entity::setScale(float _w, float _h)
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
    setSize((float)getGameWidth(), (float)getGameHeight());
    setPos(0, 0);
}
void Entity::fitToWindow()
{
    if (getGameHeight() / getGameWidth() > getH() / getW())
    {

    }
}
void Entity::setPos(float _x, float _y)
{
    position.x = _x;
    position.y = _y;
}
void Entity::setPos(Vec2 vector)
{
    setPos(vector.x, vector.y);
}
void Entity::setX(float _x)
{
    position.x = _x;
}
void Entity::setY(float _y)
{
    position.y = _y;
}
void Entity::setCPos(float _x, float _y)
{
    position.x = _x - (getW() / 2);
    position.y = _y - (getH() / 2);
}
void Entity::setCPos(Vec2 vector)
{
    setCPos(vector.x, vector.y);
}
void Entity::setCX(float _x)
{
    position.x = _x - (getW() / 2);
}
void Entity::setCY(float _y)
{
    position.y = _y - (getH() / 2);
}
void Entity::setRect(Rect rect)
{
    setPos(rect.x, rect.y);
    setSize(rect.w, rect.h);
}
Rect Entity::getRect()
{
    return { getX(), getY(), getW(), getH() };
}
void Entity::setPosCentered()
{
    setPos(getWindowCenterX(), getWindowCenterY());
}
void Entity::changePos(float _x, float _y)
{
    position.x += _x;
    position.y += _y;
}
void Entity::changePos(Vec2 vector)
{
    changePos(vector.x, vector.y);
}
Vec2 Entity::getPos()
{
    return position;
}
Vec2 Entity::getCPos()
{
    return { position.x + (getW() / 2), position.y + (getH() / 2) };
}
float Entity::getX()
{
    return position.x;
}
float Entity::getY()
{
    return position.y;
}
float Entity::getCX()
{
    return position.x + (getW() / 2);
}
float Entity::getCY()
{
    return position.y + (getH() / 2);
}
float Entity::getW()
{
    if (doClip)
    {
        return (float)clipW * scaleW;
    }
    return (float)(width)*scaleW;
}
float Entity::getH()
{
    return (float)(height)*scaleH;
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
    if (clipI * clipW >= width)
    {
        clipI = 0;
    }
}
float Entity::getWindowCenterX()
{
    return getGameWidth() / 2.0f - getW() / 2.0f;
}
float Entity::getWindowCenterY()
{
    return getGameHeight() / 2.0f - getH() / 2.0f;
}
std::string Entity::getName()
{
    return name;
}
void Entity::setName(std::string _name)
{
    name = _name;
}
float Entity::getScaleW()
{
    return scaleW;
}
float Entity::getScaleH()
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
void Entity::setRotation(float _rotation)
{
    rotation = _rotation;
}
void Entity::changeRotation(float _rotation)
{
    setRotation(getRotation() + _rotation);
}
float Entity::getRotation()
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

void Entity::setFlip(SDL_RendererFlip _flip)
{
    flip = _flip;
}

SDL_RendererFlip Entity::getFlip()
{
    return flip;
}
