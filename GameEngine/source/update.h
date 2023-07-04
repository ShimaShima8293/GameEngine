#pragma once
#include <vector>
#include <map>

typedef int (*UpdateFunc)();

// Use this as the return value for your update functions.
enum UpdateResult
{
    UPDATE_CONTINUE,
    UPDATE_END
};

// Get the number of updates running. This can be used for debugging.
size_t getUpdateCount();

// Adds a update function to the list. (It actually adds when `processUpdates` is called.)
void addUpdate(UpdateFunc _func);

// Remove a update function from the list. (It actually removes when `processUpdates` is called.)
void removeUpdate(UpdateFunc _func);

// Process and run all the update functions in the list. Call this every frame if you are using update functions.
void processUpdates();

// Clear the list. Call this when loading a scene. It's automatically called in the `initScene` function.
void clearUpdates();
