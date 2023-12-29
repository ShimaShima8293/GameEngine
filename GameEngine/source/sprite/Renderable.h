#pragma once

#include "../internal.h"
#include "../utilities.h"
#include "../render.h"

namespace GameEngine
{
    class SpriteGroup;

    struct RenderInfo
    {
        Vec2 position = { 0.0f, 0.0f };
        Vec2 scale = { 1.0f, 1.0f };
        float rotation = 0.0f;
        bool visible = true;
        SDL_RendererFlip flip = SDL_FLIP_NONE;
        Uint8 alpha = 255;
    };

    class Renderable
    {
    public:
        ~Renderable();

        // Rendering

        virtual void Render(RenderInfo info) = 0;

        // Grouping

        virtual void SetParent(SpriteGroup* parent) = 0;

        // Visibility

        virtual void SetVisibility(bool _visible) = 0;
        virtual bool GetVisibility() = 0;

        // Setting position

        virtual void SetPos(float _x, float _y) = 0;
        virtual void SetPos(Vec2 vector) = 0;
        virtual void SetCPos(float _x, float _y) = 0;
        virtual void SetCPos(Vec2 vector) = 0;

        // Changing position

        virtual void ChangePos(float _x, float _y) = 0;
        virtual void ChangePos(Vec2 vector) = 0;

        // Getting position

        virtual Vec2 GetPos() = 0;
        virtual Vec2 GetCPos() = 0;

        // Setting position (by each axis)

        virtual void SetX(float _x) = 0;
        virtual void SetY(float _y) = 0;
        virtual void SetCX(float _x) = 0;
        virtual void SetCY(float _y) = 0;

        // Getting position (by each axis)

        virtual float GetX() = 0;
        virtual float GetY() = 0;
        virtual float GetCX() = 0;
        virtual float GetCY() = 0;

        // Setting and getting rectangle

        virtual void SetRect(Rect rect) = 0;
        virtual Rect GetRect() = 0;

        // Getting sprite borders

        virtual float GetLeftB() = 0;
        virtual float GetRightB() = 0;
        virtual float GetTopB() = 0;
        virtual float GetBottomB() = 0;

        // Setting scale

        virtual void SetScale(float _w, float _h) = 0;
        virtual void SetScale(Vec2 vector) = 0;

        // Getting scale

        virtual float GetScaleW() = 0;
        virtual float GetScaleH() = 0;

        // Setting and changing size

        virtual void SetSize(float _w, float _h) = 0;
        virtual void SetSize(Vec2 vector) = 0;
        virtual void ChangeSize(float _w, float _h) = 0;
        virtual void ChangeSize(Vec2 vector) = 0;

        // Getting size

        virtual float GetW() = 0;
        virtual float GetH() = 0;

        // Setting, changing, and getting rotation

        virtual void SetRotation(float _rotation) = 0;
        virtual void ChangeRotation(float _rotation) = 0;
        virtual float GetRotation() = 0;

        // Setting and getting flip

        virtual void SetFlip(SDL_RendererFlip _flip) = 0;
        virtual SDL_RendererFlip GetFlip() = 0;

        // Useful macros for setting position and scale

        virtual void StretchToWindow() = 0;
        //virtual void fitToWindow() = 0;
        virtual void SetPosCentered() = 0;
        virtual void MoveTo(float _speed, float _angle) = 0;

        // Useful macros for getting positions

        virtual float GetAngleTowards(float x, float y) = 0;
        virtual float GetAngleTowards(Vec2 vector) = 0;
        virtual float GetWindowCenterX() = 0;
        virtual float GetWindowCenterY() = 0;

        // Setting alpha

        virtual void SetAlpha(Uint8 _alpha) = 0;
        virtual Uint8 GetAlpha() = 0;

    };


}