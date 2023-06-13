#pragma once

#include "macros.h"
#include PATH_SDL
#include <vector>
#include "Entity.h"
#include "Timer.h"


// Render everything.
void renderEverything();

void addEntity(Entity* entity);

int getEntityCount();

Entity* getEntity(int index);

int removeEntity(int index);

void clearEntities();
