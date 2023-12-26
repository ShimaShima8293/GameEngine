#pragma once
#include "internal.h"
#include "utilities.h"
#include "Scene.h"

#ifdef _WIN32
#include <SDL_syswm.h>
#define GE_HWND HWND
#else
#define GE_HWND void*
#endif

namespace GameEngine
{
    class Renderable;

    struct WindowDebugInfo
    {
        bool ShowSpriteBorders = false;
    };

    class Window
    {
    public:
        Window(std::string title, int width, int height);

        void SetTitle(std::string title);

        template <typename T, typename = std::enable_if_t<std::is_base_of<Scene, T>::value>>
        inline int LoadScene()
        {
            currentScene = std::make_unique<T>();

            return 0;
        }

        void Update();

        bool GetFocus();

        GE_HWND GetHWND();

        //void AddSprite(Renderable* sprite);

        //void SetLayers(std::vector<std::vector<Renderable*>*> _layers);

        //int GetSpriteCount();

        void RemoveSprite(Renderable* sprite) {};

        //void ClearSprites();

        typedef enum WindowMode
        {
            WINDOW_WINDOWED = 0,
            WINDOW_FULLSCREEN = 1,
            WINDOW_FULLSCREEN_DESKTOP = 4097
        } WindowMode;

        enum AxisDirection
        {
            AXIS_POSITIVE,
            AXIS_NEGATIVE
        };

        void ProcessEvents();

        bool GetMouseMoved();

        bool GetKeyPressed(SDL_KeyCode code);

        bool GetKeyPressedPulse(SDL_KeyCode code);

        bool GetJoyButton(int button);

        bool GetJoyButtonPulse(int button);

        int GetJoyAxis(int axis);

        bool GetJoyAxisPulse(int axis, AxisDirection direction, int deadzone);

        bool GetMouseButton(int button);

        bool GetMouseButtonPulse(int button);

        bool GetRunning();

        void EndMainloop();

        void Close();

        int GetGameWidth();

        int GetGameHeight();

        SDL_Window* GetSDLWindow();

        SDL_Renderer* GetSDLRenderer();

        int GetWidth();

        int GetHeight();

        void SetMode(WindowMode mode);

        WindowMode GetMode();

        int SetSystemCursor(SDL_SystemCursor _cursor);

        int HideCursor();

        Vec2 GetCursorPos();
        Vec2 GetCursorWindowPos();


        typedef enum InitFlags
        {
            INIT_ANTIALIASING = 0x01,
            INIT_DISABLE_DEBUGGING = 0x02
        } InitFlags;

        int SetFullscreenResolution(int w, int h);

        WindowDebugInfo GetDebugInfo();

        void SetDebugInfo(WindowDebugInfo debugInfo);


    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        std::unique_ptr<Scene> currentScene;
        WindowDebugInfo debugInfo;

        int gameWidth;
        int gameHeight;

        int windowID;
    };
}