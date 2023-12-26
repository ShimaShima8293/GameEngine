#pragma once

#include "core/internal.h"
#include "core/utilities.h"

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
        virtual ~Renderable();

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
        virtual void setCPos(float _x, float _y) = 0;
        virtual void setCPos(Vec2 vector) = 0;

        // Changing position

        virtual void changePos(float _x, float _y) = 0;
        virtual void changePos(Vec2 vector) = 0;

        // Getting position

        virtual Vec2 getPos() = 0;
        virtual Vec2 getCPos() = 0;

        // Setting position (by each axis)

        virtual void setX(float _x) = 0;
        virtual void setY(float _y) = 0;
        virtual void setCX(float _x) = 0;
        virtual void setCY(float _y) = 0;

        // Getting position (by each axis)

        virtual float getX() = 0;
        virtual float getY() = 0;
        virtual float getCX() = 0;
        virtual float getCY() = 0;

        // Setting and getting rectangle

        virtual void setRect(Rect rect) = 0;
        virtual Rect getRect() = 0;

        // Getting sprite borders

        virtual float getLeftB() = 0;
        virtual float getRightB() = 0;
        virtual float getTopB() = 0;
        virtual float getBottomB() = 0;

        // Setting scale

        virtual void setScale(float _w, float _h) = 0;
        virtual void setScale(Vec2 vector) = 0;

        // Getting scale

        virtual float getScaleW() = 0;
        virtual float getScaleH() = 0;

        // Setting and changing size

        virtual void setSize(float _w, float _h) = 0;
        virtual void setSize(Vec2 vector) = 0;
        virtual void changeSize(float _w, float _h) = 0;
        virtual void changeSize(Vec2 vector) = 0;

        // Getting size

        virtual float getW() = 0;
        virtual float getH() = 0;

        // Setting, changing, and getting rotation

        virtual void setRotation(float _rotation) = 0;
        virtual void changeRotation(float _rotation) = 0;
        virtual float getRotation() = 0;

        // Setting and getting flip

        virtual void setFlip(SDL_RendererFlip _flip) = 0;
        virtual SDL_RendererFlip getFlip() = 0;

        // Useful macros for setting position and scale

        virtual void stretchToWindow() = 0;
        //virtual void fitToWindow() = 0;
        virtual void setPosCentered() = 0;
        virtual void moveTo(float _speed, float _angle) = 0;

        // Useful macros for getting positions

        virtual float getAngleTowards(float x, float y) = 0;
        virtual float getAngleTowards(Vec2 vector) = 0;
        virtual float getWindowCenterX() = 0;
        virtual float getWindowCenterY() = 0;

        // Setting alpha

        virtual void setAlpha(Uint8 _alpha) = 0;
        virtual Uint8 getAlpha() = 0;

    };


}