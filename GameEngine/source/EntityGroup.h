//#pragma once
//
//#include "macros.h"
//#include PATH_SDL
//#include "Entity.h"
//#include <vector>
//
//class EntityGroup
//{
//public:
//    void addChild(Entity* entity);
//    //void addChildGroup(EntityGroup* entity);
//    std::vector<Entity*> getChildList();
//    void setChild(std::vector<Entity*> _list);
//    int getSize();
//
//    // Get the top border. This is same as `getY`
//    int getTopB();
//
//    // Get the bottom border. This will return y-axis + height.
//    int getBottomB();
//
//    // Get the left border. This is same as `getX`
//    int getLeftB();
//
//    // Get the right border. This will return x-axis + width.
//    int getRightB();
//
//    // Set the size of the texture. This changes the scale internally instead of changing the texture size.
//    // \param w The new width.
//    // \param h The new height.
//    void setSize(double _w, double _h);
//
//    // Set the size of the texture. This changes the scale internally instead of changing the texture size.
//    // \param vector The new size vector.
//    void setSize(Vec2 vector);
//
//    // Changes the size of the texture. This will do `current size * new size`. This is NOT same as `setSize` function.
//    // \param w The width to multiply.
//    // \param h The height to multiply.
//    void changeSize(double _w, double _h);
//
//    // Changes the size of the texture. This will do `current size * new size`. This is NOT same as `setSize` function.
//    // \param vector The vector to multiply.
//    void changeSize(Vec2 vector);
//
//    // Set the texture size to (getWindowWidth(), getWindowHeight()).
//    void stretchToWindow();
//
//    void fitToWindow();
//
//    // Set the entity's position.
//    // \param x The new x-axis
//    // \param y The new y-axis
//    void setPos(int _x, int _y);
//
//    // Set the entity's position.
//    // \param vector The new position vector.
//    void setPos(Vec2 vector);
//
//    void setPosCentered();
//
//    void changePos(int _x, int _y);
//
//    void changePos(Vec2 vector);
//
//    int getX();
//
//    int getY();
//
//    int getW();
//
//    int getH();
//private:
//    std::vector<Entity*> entityList;
//    SDL_Point position;
//};