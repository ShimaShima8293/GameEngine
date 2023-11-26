#pragma once
#include "Renderable.h"
#include "Sprite.h"
#include "../internal.h"
#include "../utilities.h"

namespace GameEngine
{
    class SpriteGroup : public Renderable
    {
    public:
        SpriteGroup();
        ~SpriteGroup();
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

        // SpriteGroup-specific methods:

        std::vector<Renderable*> getChildren();
        void addChild(Renderable* child);
        void removeChild(Renderable* child);
        void setChildren(std::vector<Renderable*> children);

    private:
        std::string name = "Unnamed";
        std::vector<Renderable*> children;
        RenderInfo info;
    };
}