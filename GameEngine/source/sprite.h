#pragma once

#include "internal.h"
#include "utilities.h"

typedef enum Orientation
{
    VERTICAL,
    HORIZONTAL
} Orientation;

// A higher-level abstraction of texture and rendering.
class Sprite
{
public:
    Sprite();
    ~Sprite();

    // Frees sprite's texture and initializes variables.
    void free();

    // Loads a image and set as the texture of the sprite.
    // \param path The path of the image to load.
    // \returns Returns true if the image successfully is loaded, false if not.
    bool createFromImage(std::string path);

    // Creates text texture from a font and text color.
    // \param text The text to render.
    // \param font The font to render text with.
    // \returns Returns true if the texture was successfully created, false if not.
    bool createFromText(std::string _text, TTF_Font* _font);

    // Creates texture from custom SDL_Surface.
    // \param surface The SDL_Surface struct for the texture
    // \param free (Optional) Pass false if you don't want to free the surface.
    bool createFromSurface(SDL_Surface* _surface, bool free = true);

    // Creates texture from pixels. This will create a surface with white pixels and internally call `loadFromSurface` so you don't need to manually create/free the surface.
    // \param width The width of the pixels
    // \param height The height of the pixels
    bool createSolid(int width, int height, Color color = {255, 255, 255, 255});

    bool createGradient(int length, Color color1, Color color2, Orientation orientation);

    // Replace the current texture with another one. This will automatically free the old texture.
    // \param texture A pointer to SDL_Texture.
    void setTexture(SDL_Texture* _texture, bool free = true);

    // Renders the sprite. This will automatically called if you use layer features.
    void render();

    // Changes the color modulation of the texture.
    // \param red The red value for color modulation. (0-255)
    // \param green The green value for color modulation. (0-255)
    // \param blue The blue value for color modulation. (0-255)
    void setColor(Uint8 _red, Uint8 _green, Uint8 _blue);

    // Change the color and alpha modulation of the texture.
    // \param color The Color for color modulation. (0-255)
    void setColor(Color _color);

    // Change alpha modulation of the texture.
    // \param alpha The new alpha value.
    void setAlpha(Uint8 _alpha);

    // Clear color modulation. By calling this, the render function will bypass the color modulation part.
    void clearColor();

    // Clear alpha modulation. By calling this, the render function will bypass the alpha modulation part.
    void clearAlpha();

    void moveTo(float _speed, float _angle);

    float getAngleTowards(float x, float y);

    float getAngleTowards(Vec2 vector);

    // Get the top border. This is same as `getY`.
    float getTopB();

    // Get the bottom border. This is a more readable shortcut for y-axis + height.
    float getBottomB();

    // Get the left border. This is same as `getX`.
    float getLeftB();

    // Get the right border. This is a more readable shortcut for x-axis + width.
    float getRightB();

    // Set the size of the texture. This changes the scale internally instead of changing the texture size.
    // \param w The new width.
    // \param h The new height.
    void setSize(float _w, float _h);

    // Set the size of the texture. This changes the scale internally instead of changing the texture size.
    // \param vector The new size vector.
    void setSize(Vec2 vector);

    // Changes the size of the texture. This will do `current size * new size`. This is NOT same as `setSize` function.
    // \param w The width to multiply.
    // \param h The height to multiply.
    void changeSize(float _w, float _h);

    // Changes the size of the texture. This will do `current size * new size`. This is NOT same as `setSize` function.
    // \param vector The vector to multiply.
    void changeSize(Vec2 vector);

    // Set the size to (getGameWidth(), getGameHeight()).
    void stretchToWindow();

    // Similar to `stretchToWindow` but this doesn't change the ratio.
    void fitToWindow();

    // Set the sprite's position.
    // \param x The new x-axis
    // \param y The new y-axis
    void setPos(float _x, float _y);

    // Set the sprite's position.
    // \param vector The new position vector.
    void setPos(Vec2 vector);

    void setX(float _x);

    void setY(float _y);

    void setCPos(float _x, float _y);

    void setCPos(Vec2 vector);

    void setCX(float _x);

    void setCY(float _y);

    void setRect(Rect rect);

    Rect getRect();

    // Set the sprite's position to the center of the viewport. This is a more readable shortcut for `setPos(getWindowCenterX(), getWindowCenterY())`.
    void setPosCentered();

    // Set the sprite's position relative to the current position.
    // \param x How many pixels to move horizontally.
    // \param y How many pixels to move vertically.
    void changePos(float _x, float _y);

    // Set the sprite's position relative to the current position.
    // \param vector How many pixels to move horizontally/vertically.
    void changePos(Vec2 vector);

    Vec2 getPos();

    Vec2 getCPos();

    // Returns the sprite's current x-axis.
    float getX();

    // Returns the sprite's current y-axis.
    float getY();

    // Returns the sprite's current x-axis.
    float getCX();

    // Returns the sprite's current y-axis.
    float getCY();

    // Returns the sprite's current width.
    float getW();

    // Returns the sprite's current height.
    float getH();

    // Returns the actual texture's width. It doesn't consider the scaling option.
    int getTextureW();

    // Returns the actual texture's height. It doesn't consider the scaling option.
    int getTextureH();

    // Returns the actual texture's ratio. It is a more readable shortcut for `getTextureW() / getTextureH()`.
    float getTextureRatio();

    // Set the clipping feature for the sprite.
    // \param clipW The width of the clipped texture.
    // \param clipI The index of the clipped texture.
    void setClipPos(int _clipW, int _clipI);

    // Increment the clipping index. This is a more readable shortcut for `setClipPos(width, ++index)`.
    void clipNext();

    // Set the sprite's scale. When rendering, the sprite's size will be multiplied by the scale variables.
    // \param w The scale for the width.
    // \param h The scale for the height.
    void setScale(float _w, float _h);

    // Set the sprite's scale. When rendering, the sprite's size will be multiplied by the scale variables.
    // \param vector The scale for the width/height.
    void setScale(Vec2 vector);

    float getWindowCenterX();

    float getWindowCenterY();

    float getScaleW();

    float getScaleH();

    std::string getName();

    void setName(std::string _name);

    Color getColor();

    void setText(std::string _text);

    void setRotation(float _rotation);

    void changeRotation(float _rotation);

    float getRotation();

    void setVisibility(bool _visible);

    bool getVisibility();

    void setClip(bool _doClip);

    bool getClip();

    void setFlip(SDL_RendererFlip _flip);

    SDL_RendererFlip getFlip();

    SDL_Texture* getTexture();


private:
    std::string name = "Unnamed";
    Vec2 position = {0.0f, 0.0f};
    SDL_Texture* texture = nullptr;
    int clipW = 0, clipI = 0;
    float scaleW = 1, scaleH = 1;
    int width = 0, height = 0;
    Uint8 red = 255;
    Uint8 green = 255;
    Uint8 blue = 255;
    Uint8 alpha = 255;
    bool useColorMod = false;
    bool useAlphaMod = false;
    std::string text = "";
    TTF_Font* font = NULL;
    Color textColor = { 255, 255, 255 };
    float rotation = 0.0;
    bool visible = true;
    bool doClip = false;
    bool useCommonTexture = false;
    SDL_RendererFlip flip = SDL_FLIP_NONE;

};
