#include <iostream>
#include "Entity.h"
#include "vars.h"
#include "events.h"
#include <math.h>
#include PATH_SDL
#include PATH_SDL_IMAGE
#include PATH_SDL_TTF
#include PATH_SDL_MIXER

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
    speed = 0;
    angle = 0;
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
bool Entity::loadFromImage(std::string path)
{
    free();
    SDL_Texture* newTexture = NULL;
    newTexture = IMG_LoadTexture(renderer, path.c_str());
    if (newTexture == NULL)
    {
        printError("Failed to create image texture... Entity name: " << name << " SDL Error: " << SDL_GetError());
    }
    else
    {
        SDL_QueryTexture(newTexture, NULL, NULL, &width, &height);
        texture = newTexture;
        type = ENTITY_IMAGE;
    }

    return newTexture != NULL;
}
bool Entity::loadFromText(std::string _text, TTF_Font* _font)
{
    text = _text;
    font = _font;
    textColor = { 255, 255, 255, 255 };
    free();
    SDL_Color bg = { 0, 0, 0 };
    SDL_Texture* newTexture = NULL;
    SDL_Surface* textSurface = TTF_RenderUTF8_Blended_Wrapped(font, text.c_str(), textColor, 0);
    if (textSurface == NULL)
    {
        printError("Failed to create text surface... Entity name: " << name << " SDL_TTF Error: " << TTF_GetError());
    }
    else
    {
        newTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (newTexture == NULL)
        {
            printError("Failed to create text texture... Entity name: " << name << " SDL Error: " << SDL_GetError());
        }
        else
        {
            width = textSurface->w;
            height = textSurface->h;
            texture = newTexture;
            type = ENTITY_TEXT;
        }
        SDL_FreeSurface(textSurface);
    }

    return newTexture != NULL;
}
bool Entity::loadFromSurface(SDL_Surface* _surface, bool _free)
{
    free();
    bool success = true;
    SDL_Texture* newTexture = SDL_CreateTextureFromSurface(renderer, _surface);
    if (newTexture == NULL)
    {
        success = false;
        printError("Failed to create custom texture... Entity name: " << name << " SDL Error: " << SDL_GetError());
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
    return success;
}
bool Entity::loadFromPixel(int width, int height)
{
    free();
    SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, width, height, 32, SDL_PIXELFORMAT_RGBA32);
    if (surface == NULL)
    {
        return false;
    }

    Uint32* pixels = (Uint32*)surface->pixels;

    for (int i = 0; i < width * height; i++)
    {
        pixels[i] = SDL_MapRGBA(surface->format, 255, 255, 255, 255);
    }

    if (!loadFromSurface(surface, false))
    {
        return false;
    }

    SDL_FreeSurface(surface);

    return true;
}
void Entity::setTexture(SDL_Texture* _texture)
{
    free();
    texture = _texture;
}
void Entity::render()
{
    if (getVisibility() == true)
    {
        if (useAlphaMod)
        {
            if (SDL_SetTextureAlphaMod(texture, alpha) != 0)
            {
                printError("Failed to set alpha modulation... Entity name: " << name << " SDL Error: " << SDL_GetError());
            }
        }
        if (useColorMod)
        {
            if (SDL_SetTextureColorMod(texture, red, green, blue) != 0)
            {
                printError("Failed to set color modulation... Entity name: " << name << " SDL Error: " << SDL_GetError());
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
                printError("Failed to render... Clip: True Entity name: " << name << " SDL Error: " << SDL_GetError());
            }
        }
        else
        {
            if (SDL_RenderCopyEx(renderer, texture, NULL, &rect, rotation, NULL, SDL_FLIP_NONE) != 0)
            {
                printError("Failed to render... Clip: False Entity name: " << name << " SDL Error: " << SDL_GetError());
            }
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
    useColorMod = false;
}
void Entity::clearAlpha()
{
    useAlphaMod = false;
}
// Sets the entity's angle.
// \param angle The new entity's angle. (0-359)
void Entity::setAngle(int _angle)
{
    angle = _angle;
    angle = angle % 360;
    if (angle < 0)
    {
        angle = 360 - (angle * -1);
    }
}
void Entity::changeAngle(int _angle)
{
    // angle = (_angle + angle) % 360;
    setAngle(angle + _angle);
}
void Entity::moveTo(int _speed, int _angle)
{
    changePos((int)(std::round(speed * std::sin(angle * 3.14 / 180))), (int)(std::round(speed * std::cos(angle * 3.14 / 180))));
}
void Entity::moveFoward(int multiple)
{
    changePos((int)(std::round(speed * multiple * std::sin(angle * 3.1415 / 180))), (int)(std::round(speed * multiple * std::cos(angle * 3.14 / 180))));
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
    setSize(getWindowWidth(), getWindowHeight());
    setPos(0, 0);
}
void Entity::fitToWindow()
{
    if (getWindowHeight() / getWindowWidth() > getH() / getW())
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
    setPos(vector.x, vector.y);
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
    changePos(vector.x, vector.y);
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
    return getWindowWidth() / 2 - getW() / 2;
}
int Entity::getWindowCenterY()
{
    return getWindowHeight() / 2 - getH() / 2;
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
// Use this if you are only changing the text. Its lighter than `loadFromText`
void Entity::setText(std::string _text)
{
    if (text != _text)
    {
        loadFromText(_text, font);
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
