# GameEngine

This is an library I made to simplify SDL2. If you use this library, you can create simple 2D games without using SDL manually.

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
