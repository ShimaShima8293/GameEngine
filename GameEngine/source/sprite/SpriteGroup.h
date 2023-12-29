#pragma once
#include "../internal.h"
#include "../utilities.h"
#include "Renderable.h"

namespace GameEngine
{
    class SpriteGroup : public Renderable
    {
    public:
        SpriteGroup();
        ~SpriteGroup();
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

        // Setting alpha

        void SetAlpha(Uint8 _alpha);
        Uint8 GetAlpha();

        // SpriteGroup-specific methods:

        std::vector<Renderable*> GetChildren();
        void AddChild(Renderable* child);
        void RemoveChild(Renderable* child);
        void SetChildren(std::vector<Renderable*> children);

    private:
        std::string name = "Unnamed";
        std::vector<Renderable*> children;
        RenderInfo info;
    };
}