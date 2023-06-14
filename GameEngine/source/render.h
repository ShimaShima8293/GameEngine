#pragma once

#include "macros.h"
#include PATH_SDL
#include <vector>
#include "Entity.h"
#include "Timer.h"


// Render entities and update the window. This function will delay for about 16 miliseconds to maintain 60 fps.
void renderEverything();

// Add an entity to the rendering list. This function is required for an entity to be rendered.
// \param entity A pointer to an entity.
void addEntity(Entity* entity);

// Get the total number of entities in the rendering list.
// \returns Returns the number of entities in the rendering list.
int getEntityCount();

// Get an entity from the rendering list.
// \param index The index of the entity in the rendering list.
// \returns Returns the pointer to the requested entity.
Entity* getEntity(int index);

// Remove an entity from the rendering list.
// \param index The index of the entity to remove.
// \returns Returns 0 if it succeeded, -1 if it didn't.
int removeEntity(int index);

// Remove all entities from the rendering list. This doesn't free or modify the entities.
void clearEntities();
