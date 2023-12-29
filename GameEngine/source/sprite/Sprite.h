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
        void Free();

        // Renderable methods:

        // Rendering

        void Render(RenderInfo info);

        // Grouping

        void SetParent(SpriteGroup* parent);

        // Visibility

        void SetVisibility(bool _visible);
        bool GetVisibility();

        // Setting position

        void SetPos(float _x, float _y);
        void SetPos(Vec2 vector);
        void SetCPos(float _x, float _y);
        void SetCPos(Vec2 vector);

        // Changing position

        void ChangePos(float _x, float _y);
        void ChangePos(Vec2 vector);

        // Getting position

        Vec2 GetPos();
        Vec2 GetCPos();

        // Setting position (by each axis)

        void SetX(float _x);
        void SetY(float _y);
        void SetCX(float _x);
        void SetCY(float _y);

        // Getting position (by each axis)

        float GetX();
        float GetY();
        float GetCX();
        float GetCY();

        // Setting and getting rectangle

        void SetRect(Rect rect);
        Rect GetRect();

        // Getting sprite borders

        float GetLeftB();
        float GetRightB();
        float GetTopB();
        float GetBottomB();

        // Setting scale

        void SetScale(float _w, float _h);
        void SetScale(Vec2 vector);

        // Getting scale

        float GetScaleW();
        float GetScaleH();

        // Setting and changing size

        void SetSize(float _w, float _h);
        void SetSize(Vec2 vector);
        void ChangeSize(float _w, float _h);
        void ChangeSize(Vec2 vector);

        // Getting size

        float GetW();
        float GetH();

        // Setting, changing, and getting rotation

        void SetRotation(float _rotation);
        void ChangeRotation(float _rotation);
        float GetRotation();

        // Setting and getting flip

        void SetFlip(SDL_RendererFlip _flip);
        SDL_RendererFlip GetFlip();

        // Useful macros for setting position and scale

        void StretchToWindow();
        //void fitToWindow();
        void SetPosCentered();
        void MoveTo(float _speed, float _angle);

        // Useful macros for getting positions

        float GetAngleTowards(float x, float y);
        float GetAngleTowards(Vec2 vector);
        float GetWindowCenterX();
        float GetWindowCenterY();

        // Setting and getting alpha

        void SetAlpha(Uint8 _alpha);
        Uint8 GetAlpha();

        // Sprite-specific methods:

        // Loads a image and set as the texture of the sprite.
        // \param path The path of the image to load.
        // \returns Returns true if the image successfully is loaded, false if not.
        bool CreateFromImage(std::string path);

        // Creates text texture from a font and text color.
        // \param text The text to render.
        // \param font The font to render text with.
        // \returns Returns true if the texture was successfully created, false if not.
        bool CreateFromText(std::string _text, TTF_Font* _font);

        // Creates texture from custom SDL_Surface.
        // \param surface The SDL_Surface struct for the texture
        // \param free (Optional) Pass false if you don't want to free the surface.
        bool CreateFromSurface(SDL_Surface* _surface, bool free = true);

        // Creates texture from pixels. This will create a surface with white pixels and internally call `loadFromSurface` so you don't need to manually create/free the surface.
        // \param width The width of the pixels
        // \param height The height of the pixels
        bool CreateSolid(int width, int height, Color color = { 255, 255, 255, 255 });

        bool CreateGradient(int length, Color color1, Color color2, Orientation orientation);

        // Replace the current texture with another one. This will automatically free the old texture.
        // \param texture A pointer to SDL_Texture.
        void SetTexture(SDL_Texture* _texture, bool free = true);

        // Changes the color modulation of the texture.
        // \param red The red value for color modulation. (0-255)
        // \param green The green value for color modulation. (0-255)
        // \param blue The blue value for color modulation. (0-255)
        void SetColor(Uint8 _red, Uint8 _green, Uint8 _blue);

        // Change the color and alpha modulation of the texture.
        // \param color The Color for color modulation. (0-255)
        void SetColor(Color _color);

        // Clear color modulation. By calling this, the render function will bypass the color modulation part.
        void ClearColor();

        // Clear alpha modulation. By calling this, the render function will bypass the alpha modulation part.
        void ClearAlpha();

        // Returns the actual texture's width. It doesn't consider the scaling option.
        int GetTextureW();

        // Returns the actual texture's height. It doesn't consider the scaling option.
        int GetTextureH();

        // Returns the actual texture's ratio. It is a more readable shortcut for `GetTextureW() / GetTextureH()`.
        float GetTextureRatio();

        // Set the clipping feature for the sprite.
        // \param clipW The width of the clipped texture.
        // \param clipI The index of the clipped texture.
        void SetClipPos(int _clipW, int _clipI);

        // Increment the clipping index. This is a more readable shortcut for `SetClipPos(width, ++index)`.
        void ClipNext();

        std::string GetName();

        void SetName(std::string _name);

        Color GetColor();

        void SetText(std::string _text);

        void SetClip(bool _doClip);

        bool GetClip();

        SDL_Texture* GetTexture();


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