#include "../sprite.h"

namespace GameEngine
{
    SpriteGroup::SpriteGroup()
    {
        Free();
    }
    SpriteGroup::~SpriteGroup()
    {
        Free();
    }

    void SpriteGroup::Free()
    {
        for (Renderable* child : this->children)
        {
            //child->Free();
        }
        this->children.clear();
        this->info = {};
    }

    void SpriteGroup::Render(RenderInfo info)
    {
        if (this->info.visible == false)
        {
            return;
        }
        RenderInfo newInfo{};
        newInfo.position = this->info.position + info.position;
        newInfo.rotation = this->info.rotation + info.rotation;
        newInfo.scale = this->info.scale * info.scale;
        newInfo.alpha = (Uint8)std::round(info.alpha * ((float)this->info.alpha / 255.0f));

        for (Renderable* child : this->children)
        {
            child->Render(newInfo);
        }
    }

    void SpriteGroup::SetParent(SpriteGroup* parent)
    {
    }

    void SpriteGroup::SetVisibility(bool _visible)
    {
        this->info.visible = _visible;
    }

    bool SpriteGroup::GetVisibility()
    {
        return this->info.visible;
    }

    void SpriteGroup::SetPos(float _x, float _y)
    {
        this->SetPos({ _x, _y });
    }

    void SpriteGroup::SetPos(Vec2 vector)
    {
        this->info.position = vector;
    }

    void SpriteGroup::SetCPos(float _x, float _y)
    {
        this->SetCPos({ _x, _y });
    }

    void SpriteGroup::SetCPos(Vec2 vector)
    {
        this->info.position = vector;
    }

    std::vector<Renderable*> SpriteGroup::GetChildren()
    {
        return this->children;
    }

    void SpriteGroup::AddChild(Renderable* child)
    {
        for (int i = 0; i < this->children.size(); i++)
        {
            if (child == this->children[i])
            {
                PrintErrorGE("SpriteGroup::AddChild: Trying to add an existing child. Don't forGet to call `Init()`");
                return;
            }
        }
        this->children.push_back(child);
    }

    void SpriteGroup::RemoveChild(Renderable* child)
    {
        for (int i = 0; i < this->children.size(); i++)
        {
            if (child == this->children[i])
            {
                this->children.erase(this->children.begin() + i);
                i--;
            }
        }
    }

    void SpriteGroup::SetChildren(std::vector<Renderable*> children)
    {
        this->children = children;
    }

    void SpriteGroup::ChangePos(float x, float y)
    {
        this->ChangePos({ x, y });
    }

    void SpriteGroup::ChangePos(Vec2 vector)
    {
        this->info.position = this->info.position + vector;
    }
    Vec2 SpriteGroup::GetPos()
    {
        return this->info.position;
    }
    Vec2 SpriteGroup::GetCPos()
    {
        return { this->info.position.x + (GetW() / 2.0f), this->info.position.y + (GetH() / 2.0f) };
    }
    void SpriteGroup::SetX(float _x)
    {
        this->info.position.x = _x;
    }
    void SpriteGroup::SetY(float _y)
    {
        this->info.position.y = _y;
    }
    void SpriteGroup::SetCX(float _x)
    {
        this->info.position.x = _x - this->GetW() / 2.0f;
    }
    void SpriteGroup::SetCY(float _y)
    {
        this->info.position.y = _y - this->GetH() / 2.0f;
    }
    float SpriteGroup::GetX()
    {
        return this->info.position.x;
    }
    float SpriteGroup::GetY()
    {
        return this->info.position.y;
    }
    float SpriteGroup::GetCX()
    {
        return this->info.position.x + this->GetW() / 2.0f;
    }
    float SpriteGroup::GetCY()
    {
        return this->info.position.y + this->GetH() / 2.0f;
    }
    void SpriteGroup::SetRect(Rect rect)
    {
        this->SetPos(rect.x, rect.y);
        this->SetSize(rect.w, rect.h);
    }
    Rect SpriteGroup::GetRect()
    {
        return { this->GetX(), this->GetY(), this->GetW(), this->GetH() };
    }
    float SpriteGroup::GetLeftB()
    {
        return this->GetX();
    }
    float SpriteGroup::GetRightB()
    {
        return this->GetX() + this->GetW();
    }
    float SpriteGroup::GetTopB()
    {
        return this->GetY();
    }
    float SpriteGroup::GetBottomB()
    {
        return this->GetY() + this->GetH();
    }
    void SpriteGroup::SetScale(float _w, float _h)
    {
        this->SetScale({ _w, _h });
    }
    void SpriteGroup::SetScale(Vec2 vector)
    {
        this->info.scale = vector;
    }
    float SpriteGroup::GetScaleW()
    {
        return this->info.scale.x;
    }
    float SpriteGroup::GetScaleH()
    {
        return this->info.scale.y;
    }
    void SpriteGroup::SetSize(float _w, float _h)
    {
    }
    void SpriteGroup::SetSize(Vec2 vector)
    {
    }
    void SpriteGroup::ChangeSize(float _w, float _h)
    {
    }
    void SpriteGroup::ChangeSize(Vec2 vector)
    {
    }
    float SpriteGroup::GetW()
    {
        return 0.0f;
    }
    float SpriteGroup::GetH()
    {
        return 0.0f;
    }
    void SpriteGroup::SetRotation(float _rotation)
    {
    }
    void SpriteGroup::ChangeRotation(float _rotation)
    {
    }
    float SpriteGroup::GetRotation()
    {
        return 0.0f;
    }
    void SpriteGroup::SetFlip(SDL_RendererFlip _flip)
    {
    }
    SDL_RendererFlip SpriteGroup::GetFlip()
    {
        return SDL_RendererFlip();
    }
    void SpriteGroup::StretchToWindow()
    {
    }
    void SpriteGroup::SetPosCentered()
    {
    }
    void SpriteGroup::MoveTo(float _speed, float _angle)
    {
    }
    float SpriteGroup::GetAngleTowards(float x, float y)
    {
        return 0.0f;
    }
    float SpriteGroup::GetAngleTowards(Vec2 vector)
    {
        return 0.0f;
    }
    float SpriteGroup::GetWindowCenterX()
    {
        return 0.0f;
    }
    float SpriteGroup::GetWindowCenterY()
    {
        return 0.0f;
    }
    void SpriteGroup::SetAlpha(Uint8 _alpha)
    {
        info.alpha = _alpha;
    }
    Uint8 SpriteGroup::GetAlpha()
    {
        return info.alpha;
    }
}