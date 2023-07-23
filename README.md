# GameEngine

This is an library I made to simplify SDL2. If you use this library, you can create simple 2D games without using SDL manually.

## Quick View

1. Initialize the library and create a window by calling `init()`.
2. Create & modify entities.
3. Add entities to the rendering queue.

These are the basic steps this library make when rendering.

## How to Create a Window

This is the minimal code you need to write to create a window:
```cpp
#include <gameEngine.h>

int main(int argc, char* args[])
{
    init("Hello!", 1920, 1080, 0);
    startMainloop();

    return 0;
}
```

## Entity

Entity is a class that represents a single texture to be rendered. You can create a blank entity like following:
```cpp
Entity entity; // stack allocation
Entity* entity = new Entity; // heap allocation
```

### Creating Texture

Your entity doesn't have any texture when you create. So, you will need to create one with the following functions:
- `bool Entity::createFromImage(std::string path)`
- `bool Entity::createFromText(std::string _text, TTF_Font* _font)`
- `bool Entity::createFromSurface(SDL_Surface* _surface, bool _free)`
- `bool Entity::createSolid(int width, int height, SDL_Color color)`
- `bool Entity::createGradient(int length, SDL_Color color1, SDL_Color color2, Orientation orientation)`
- `void Entity::setTexture(SDL_Texture* _texture, bool _free)`

### Modifying Entities
You can move, change color, change size, apply rotation to your entities by the following functions:
#### Position
- `void Entity::setPos(float _x, float _y)`
- `void Entity::setPos(Vec2 vector)`
- `void Entity::setX(float _x)`
- `void Entity::setY(float _y)`
- `void Entity::setCPos(Vec2 vector)`
- `void Entity::setCPos(float _x, float _y)`
- `void Entity::setCX(float _x)`
- `void Entity::setCY(float _y)`
- `void Entity::setPosCentered()`
- `void Entity::changePos(float _x, float _y)`
#### Clipping
- `void Entity::setClipPos(int _clipW, int _clipI = 0)`
- `void Entity::changePos(Vec2 vector)`
- `void Entity::clipNext()`
- `void Entity::setClip(bool _doClip)`
#### Rotation
- `void Entity::setRotation(float _rotation)`
- `void Entity::changeRotation(float _rotation)`
#### Visibility
- `void Entity::setVisibility(bool _visible)`
#### 

## Audio
### Opening a Audio File
### Playing a Sound

## Resources
This library handles WAV chunks and fonts. You can manage them using the following functions:
### Opening a Resource
- `TTF_Font* openFont(std::string path, int size)`
- `Mix_Chunk* openWAV(std::string path)`
### Closing a Resource
- `void closeFont(TTF_Font* font)`
- `void closeWAV(Mix_Chunk* chunk)`
- `void closeResources()`
