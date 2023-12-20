#pragma once
#include "Renderable.h"
#include "SpriteGroup.h"

namespace GameEngine
{
    enum Orientation
    {
        VERTICAL,
        HORIZONTAL
    };


    // A higher-level abstraction of texture and rendering.
    class Sprite : public Renderable
    {
    public:
        Sprite();
        ~Sprite();

        // Frees sprite's texture and initializes variables.
        void free();

        // Renderable methods:

        // Rendering

        void render(RenderInfo info);

        // Grouping

        void setParent(SpriteGroup* parent);

        // Visibility

        void setVisibility(bool _visible);
        bool getVisibility();

        // Setting position

        void setPos(float _x, float _y);
        void setPos(Vec2 vector);
        void setCPos(float _x, float _y);
        void setCPos(Vec2 vector);

        // Changing position

        void changePos(float _x, float _y);
        void changePos(Vec2 vector);

        // Getting position

        Vec2 getPos();
        Vec2 getCPos();

        // Setting position (by each axis)

        void setX(float _x);
        void setY(float _y);
        void setCX(float _x);
        void setCY(float _y);

        // Getting position (by each axis)

        float getX();
        float getY();
        float getCX();
        float getCY();

        // Setting and getting rectangle

        void setRect(Rect rect);
        Rect getRect();

        // Getting sprite borders

        float getLeftB();
        float getRightB();
        float getTopB();
        float getBottomB();

        // Setting scale

        void setScale(float _w, float _h);
        void setScale(Vec2 vector);

        // Getting scale

        float getScaleW();
        float getScaleH();

        // Setting and changing size

        void setSize(float _w, float _h);
        void setSize(Vec2 vector);
        void changeSize(float _w, float _h);
        void changeSize(Vec2 vector);

        // Getting size

        float getW();
        float getH();

        // Setting, changing, and getting rotation

        void setRotation(float _rotation);
        void changeRotation(float _rotation);
        float getRotation();

        // Setting and getting flip

        void setFlip(SDL_RendererFlip _flip);
        SDL_RendererFlip getFlip();

        // Useful macros for setting position and scale

        void stretchToWindow();
        //void fitToWindow();
        void setPosCentered();
        void moveTo(float _speed, float _angle);

        // Useful macros for getting positions

        float getAngleTowards(float x, float y);
        float getAngleTowards(Vec2 vector);
        float getWindowCenterX();
        float getWindowCenterY();

        // Setting and getting alpha

        void setAlpha(Uint8 _alpha);
        Uint8 getAlpha();

        // Sprite-specific methods:

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
        bool createSolid(int width, int height, Color color = { 255, 255, 255, 255 });

        bool createGradient(int length, Color color1, Color color2, Orientation orientation);

        // Replace the current texture with another one. This will automatically free the old texture.
        // \param texture A pointer to SDL_Texture.
        void setTexture(SDL_Texture* _texture, bool free = true);

        // Changes the color modulation of the texture.
        // \param red The red value for color modulation. (0-255)
        // \param green The green value for color modulation. (0-255)
        // \param blue The blue value for color modulation. (0-255)
        void setColor(Uint8 _red, Uint8 _green, Uint8 _blue);

        // Change the color and alpha modulation of the texture.
        // \param color The Color for color modulation. (0-255)
        void setColor(Color _color);

        // Clear color modulation. By calling this, the render function will bypass the color modulation part.
        void clearColor();

        // Clear alpha modulation. By calling this, the render function will bypass the alpha modulation part.
        void clearAlpha();

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

        std::string getName();

        void setName(std::string _name);

        Color getColor();

        void setText(std::string _text);

        void setClip(bool _doClip);

        bool getClip();

        SDL_Texture* getTexture();


    private:
        std::string name = "Unnamed";
        Vec2 position = { 0.0f, 0.0f };
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
        SpriteGroup* parent = nullptr;

    };
}