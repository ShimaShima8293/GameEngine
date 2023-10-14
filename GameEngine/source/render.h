#pragma once
#include "internal.h"
#include "sprite.h"

// Render sprites and update the window. This function will delay for about 16 miliseconds to maintain 60 fps.
void renderEverything();

// Add an sprite to the rendering list. You can use either this function or the `setLayers` function to add a sprite to the rendering queue. If there are sprites added by the `setLayers` function, sprites added by this function will be rendered under them.
// \param sprite A pointer to an sprite.
void addSprite(Sprite* sprite);

void setLayers(std::vector<std::vector<Sprite*>*> _layers);

// Get the total number of sprites in the rendering list.
// \returns Returns the number of sprites in the rendering list.
int getSpriteCount();

// Get an sprite from the rendering list.
// \param index The index of the sprite in the rendering list.
// \returns Returns the pointer to the requested sprite.
Sprite* getSprite(int index);

// Remove an sprite from the rendering list.
void removeSprite(Sprite* sprite);

// Remove all sprites from the rendering list. This doesn't free or modify the sprites.
void clearSprites();
