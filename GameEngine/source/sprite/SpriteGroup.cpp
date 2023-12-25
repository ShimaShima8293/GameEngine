#include "../sprite.h"

namespace GameEngine
{
    SpriteGroup::SpriteGroup()
    {
        free();
    }
    SpriteGroup::~SpriteGroup()
    {
        free();
    }

    void SpriteGroup::free()
    {
        for (Renderable* child : this->children)
        {
            //child->free();
        }
        this->children.clear();
        this->info = {};
    }

    void SpriteGroup::render(RenderInfo info)
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
            child->render(newInfo);
        }
    }

    void SpriteGroup::setParent(SpriteGroup* parent)
    {
    }

    void SpriteGroup::setVisibility(bool _visible)
    {
        this->info.visible = _visible;
    }

    bool SpriteGroup::getVisibility()
    {
        return this->info.visible;
    }

    void SpriteGroup::setPos(float _x, float _y)
    {
        this->setPos({ _x, _y });
    }

    void SpriteGroup::setPos(Vec2 vector)
    {
        this->info.position = vector;
    }

    void SpriteGroup::setCPos(float _x, float _y)
    {
        this->setCPos({ _x, _y });
    }

    void SpriteGroup::setCPos(Vec2 vector)
    {
        this->info.position = vector;
    }

    std::vector<Renderable*> SpriteGroup::getChildren()
    {
        return this->children;
    }

    void SpriteGroup::addChild(Renderable* child)
    {
        for (int i = 0; i < this->children.size(); i++)
        {
            if (child == this->children[i])
            {
                PrintErrorInternal("SpriteGroup::addChild: Trying to add an existing child. Don't forget to call `init()`");
                return;
            }
        }
        this->children.push_back(child);
    }

    void SpriteGroup::removeChild(Renderable* child)
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

    void SpriteGroup::setChildren(std::vector<Renderable*> children)
    {
        this->children = children;
    }

    void SpriteGroup::changePos(float x, float y)
    {
        this->changePos({ x, y });
    }

    void SpriteGroup::changePos(Vec2 vector)
    {
        this->info.position = this->info.position + vector;
    }
    Vec2 SpriteGroup::getPos()
    {
        return this->info.position;
    }
    Vec2 SpriteGroup::getCPos()
    {
        return { this->info.position.x + (getW() / 2.0f), this->info.position.y + (getH() / 2.0f) };
    }
    void SpriteGroup::setX(float _x)
    {
        this->info.position.x = _x;
    }
    void SpriteGroup::setY(float _y)
    {
        this->info.position.y = _y;
    }
    void SpriteGroup::setCX(float _x)
    {
        this->info.position.x = _x - this->getW() / 2.0f;
    }
    void SpriteGroup::setCY(float _y)
    {
        this->info.position.y = _y - this->getH() / 2.0f;
    }
    float SpriteGroup::getX()
    {
        return this->info.position.x;
    }
    float SpriteGroup::getY()
    {
        return this->info.position.y;
    }
    float SpriteGroup::getCX()
    {
        return this->info.position.x + this->getW() / 2.0f;
    }
    float SpriteGroup::getCY()
    {
        return this->info.position.y + this->getH() / 2.0f;
    }
    void SpriteGroup::setRect(Rect rect)
    {
        this->setPos(rect.x, rect.y);
        this->setSize(rect.w, rect.h);
    }
    Rect SpriteGroup::getRect()
    {
        return { this->getX(), this->getY(), this->getW(), this->getH() };
    }
    float SpriteGroup::getLeftB()
    {
        return this->getX();
    }
    float SpriteGroup::getRightB()
    {
        return this->getX() + this->getW();
    }
    float SpriteGroup::getTopB()
    {
        return this->getY();
    }
    float SpriteGroup::getBottomB()
    {
        return this->getY() + this->getH();
    }
    void SpriteGroup::setScale(float _w, float _h)
    {
        this->setScale({ _w, _h });
    }
    void SpriteGroup::setScale(Vec2 vector)
    {
        this->info.scale = vector;
    }
    float SpriteGroup::getScaleW()
    {
        return this->info.scale.x;
    }
    float SpriteGroup::getScaleH()
    {
        return this->info.scale.y;
    }
    void SpriteGroup::setSize(float _w, float _h)
    {
    }
    void SpriteGroup::setSize(Vec2 vector)
    {
    }
    void SpriteGroup::changeSize(float _w, float _h)
    {
    }
    void SpriteGroup::changeSize(Vec2 vector)
    {
    }
    float SpriteGroup::getW()
    {
        return 0.0f;
    }
    float SpriteGroup::getH()
    {
        return 0.0f;
    }
    void SpriteGroup::setRotation(float _rotation)
    {
    }
    void SpriteGroup::changeRotation(float _rotation)
    {
    }
    float SpriteGroup::getRotation()
    {
        return 0.0f;
    }
    void SpriteGroup::setFlip(SDL_RendererFlip _flip)
    {
    }
    SDL_RendererFlip SpriteGroup::getFlip()
    {
        return SDL_RendererFlip();
    }
    void SpriteGroup::stretchToWindow()
    {
    }
    void SpriteGroup::setPosCentered()
    {
    }
    void SpriteGroup::moveTo(float _speed, float _angle)
    {
    }
    float SpriteGroup::getAngleTowards(float x, float y)
    {
        return 0.0f;
    }
    float SpriteGroup::getAngleTowards(Vec2 vector)
    {
        return 0.0f;
    }
    float SpriteGroup::getWindowCenterX()
    {
        return 0.0f;
    }
    float SpriteGroup::getWindowCenterY()
    {
        return 0.0f;
    }
    void SpriteGroup::setAlpha(Uint8 _alpha)
    {
        info.alpha = _alpha;
    }
    Uint8 SpriteGroup::getAlpha()
    {
        return info.alpha;
    }
}