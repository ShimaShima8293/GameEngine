#pragma once
#include "internal.h"

namespace GameEngine
{
    class Renderable;

    // Render sprites and update the window. This function will delay for about 16 miliseconds to maintain 60 fps.
    void RenderEverything();

    // Add an sprite to the rendering list. You can use either this function or the `SetLayers()`  to add a sprite to the rendering queue. If there are sprites added by the `SetLayers()` function, sprites added by this function will be rendered under them.
    // \param sprite A pointer to an sprite.
    void AddSprite(Renderable* sprite);

    // Set the order of layers to be rendered. Sprites added by this function will be rendered above those added with the `AddSprite()` function. So, I recommend not using this function and `AddSprite()` in the same scene.
    void SetLayers(std::vector<std::vector<Renderable*>*> _layers);

    // Get the total number of sprites in the rendering list.
    // \returns Returns the number of sprites in the rendering list.
    int GetSpriteCount();

    // Remove an sprite from the rendering list.
    void RemoveSprite(Renderable* sprite);

    // Remove all sprites from the rendering list. This doesn't free or modify the sprites.
    void ClearSprites();
}