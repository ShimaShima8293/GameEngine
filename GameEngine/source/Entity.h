#pragma once

#include "macros.h"
#include "utilities.h"
#include <iostream>
#include PATH_SDL
#include PATH_SDL_IMAGE
#include PATH_SDL_TTF
#include <vector>

typedef enum EntityType
{
    ENTITY_NULL,
    ENTITY_IMAGE,
    ENTITY_TEXT,
    ENTITY_CUSTOM
} EntityType;


// A higher-level abstraction of texture and rendering.
class Entity
{
public:
    double speed = 0;
    int angle = 0;

    Entity();
    ~Entity();

    // Frees entity's texture and initializes variables.
    void free();

    // Loads a image and set as the texture of the entity.
    // \param path The path of the image to load.
    // \returns Returns true if the image successfully is loaded, false if not.
    bool loadFromImage(std::string path);

    // Creates text texture from a font and text color.
    // \param text The text to render.
    // \param font The font to render text with.
    // \returns Returns true if the texture was successfully created, false if not.
    bool loadFromText(std::string _text, TTF_Font* _font);

    // Creates texture from custom SDL_Surface.
    // \param surface The SDL_Surface struct for the texture
    // \param free (Optional) Pass false if you don't want to free the surface.
    bool loadFromSurface(SDL_Surface* _surface, bool free = true);

    // Creates texture from pixels. This will create a surface with white pixels and internally call `loadFromSurface` so you don't need to manually create/free the surface.
    // \param width The width of the pixels
    // \param height The height of the pixels
    bool loadFromPixel(int width, int height);

    // Replace the current texture with another one. This will automatically free the old texture.
    // \param texture A pointer to SDL_Texture.
    void setTexture(SDL_Texture* _texture);

    // Renders the entity. This will automatically called if you use layer features.
    void render();

    // Changes the color modulation of the texture.
    // \param red The red value for color modulation. (0-255)
    // \param green The green value for color modulation. (0-255)
    // \param blue The blue value for color modulation. (0-255)
    void setColor(Uint8 _red, Uint8 _green, Uint8 _blue);

    // Change the color and alpha modulation of the texture.
    // \param color The SDL_Color for color modulation. (0-255)
    void setColor(SDL_Color _color);

    // Change alpha modulation of the texture.
    // \param alpha The new alpha value.
    void setAlpha(Uint8 _alpha);

    // Clear color modulation. By calling this, the render function will bypass the color modulation part.
    void clearColor();

    // Clear alpha modulation. By calling this, the render function will bypass the alpha modulation part.
    void clearAlpha();

    void setAngle(int _angle);

    void changeAngle(int _angle);

    void moveTo(int _speed, int _angle);

    void moveFoward(int multiple = 1);

    // Get the top border. This is same as `getY`.
    int getTopB();

    // Get the bottom border. This is a more readable shortcut for y-axis + height.
    int getBottomB();

    // Get the left border. This is same as `getX`.
    int getLeftB();

    // Get the right border. This is a more readable shortcut for x-axis + width.
    int getRightB();

    // Set the size of the texture. This changes the scale internally instead of changing the texture size.
    // \param w The new width.
    // \param h The new height.
    void setSize(double _w, double _h);

    // Set the size of the texture. This changes the scale internally instead of changing the texture size.
    // \param vector The new size vector.
    void setSize(Vec2 vector);

    // Changes the size of the texture. This will do `current size * new size`. This is NOT same as `setSize` function.
    // \param w The width to multiply.
    // \param h The height to multiply.
    void changeSize(double _w, double _h);

    // Changes the size of the texture. This will do `current size * new size`. This is NOT same as `setSize` function.
    // \param vector The vector to multiply.
    void changeSize(Vec2 vector);

    // Set the size to (getGameWidth(), getGameHeight()).
    void stretchToWindow();

    // Similar to `stretchToWindow` but this doesn't change the ratio.
    void fitToWindow();

    // Set the entity's position.
    // \param x The new x-axis
    // \param y The new y-axis
    void setPos(int _x, int _y);

    // Set the entity's position.
    // \param vector The new position vector.
    void setPos(Vec2 vector);

    // Set the entity's position to the center of the viewport. This is a more readable shortcut for `setPos(getWindowCenterX(), getWindowCenterY())`.
    void setPosCentered();

    // Set the entity's position relative to the current position.
    // \param x How many pixels to move horizontally.
    // \param y How many pixels to move vertically.
    void changePos(int _x, int _y);

    // Set the entity's position relative to the current position.
    // \param vector How many pixels to move horizontally/vertically.
    void changePos(Vec2 vector);

    // Returns the entity's current x-axis.
    int getX();

    // Returns the entity's current y-axis.
    int getY();

    // Returns the entity's current width.
    int getW();

    // Returns the entity's current height.
    int getH();

    // Returns the actual texture's width. It doesn't consider the scaling option.
    int getTextureW();

    // Returns the actual texture's height. It doesn't consider the scaling option.
    int getTextureH();

    // Returns the actual texture's ratio. It is a more readable shortcut for `getTextureW() / getTextureH()`.
    float getTextureRatio();

    // Set the clipping feature for the entity.
    // \param clipW The width of the clipped texture.
    // \param clipI The index of the clipped texture.
    void setClipPos(int _clipW, int _clipI);

    // Increment the clipping index. This is a more readable shortcut for `setClipPos(width, ++index)`.
    void clipNext();

    // Set the entity's scale. When rendering, the entity's size will be multiplied by the scale variables.
    // \param w The scale for the width.
    // \param h The scale for the height.
    void setScale(double _w, double _h);

    // Set the entity's scale. When rendering, the entity's size will be multiplied by the scale variables.
    // \param vector The scale for the width/height.
    void setScale(Vec2 vector);

    int getWindowCenterX();

    int getWindowCenterY();

    double getScaleW();

    double getScaleH();

    std::string getName();

    void setName(std::string _name);

    SDL_Color getColor();

    EntityType type = ENTITY_NULL;

    void setText(std::string _text);

    void setRotation(double _rotation);

    void changeRotation(double _rotation);

    double getRotation();

    void setVisibility(bool _visible);

    bool getVisibility();

    void setClip(bool _doClip);

    bool getClip();


private:
    std::string name = "Unnamed";
    SDL_Point position;
    SDL_Texture* texture = nullptr;
    SDL_Rect rect = {};
    SDL_Rect clipRect = {};
    int clipW = 0, clipI = 0;
    double scaleW = 1, scaleH = 1;
    int width = 0, height = 0;
    Uint8 red = 255;
    Uint8 green = 255;
    Uint8 blue = 255;
    Uint8 alpha = 255;
    bool useColorMod = false;
    bool useAlphaMod = false;
    std::string text = "";
    TTF_Font* font = NULL;
    SDL_Color textColor = { 255, 255, 255 };
    double rotation;
    bool visible = true;
    bool doClip = false;

};
