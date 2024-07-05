#include "PopupOutput.h"
#include "callerData.h"

#include "render/Window.h"

#include <SDL.h>

#include <filesystem>
#include <source_location>

#ifdef _WIN32
#include <Windows.h>
#endif

namespace GameEngine
{
    PopupOutput::PopupOutput(Window& window, const std::filesystem::path& sourceDir) :
        PopupOutput(window, DebugOutput::DEBUG_LEVEL_ERROR, DebugOutput::DEBUG_LEVEL_ERROR, sourceDir)
    {
    }

    PopupOutput::PopupOutput(Window& window, DebugLevel level, DebugLevel levelGE, const std::filesystem::path& sourceDir) :
        window(window),
        level(level),
        levelGE(levelGE),
        sourceDir(sourceDir)
    {

    }

    void PopupOutput::Info(std::string text, const std::source_location& location)
    {
#ifdef _WIN32
        MessageBoxA(window.GetHWND(), ("An information from the application.\n\n" + GetCallerData(location, sourceDir) + ":\n" + text).c_str(), "Information", MB_ICONINFORMATION | MB_OK);
#endif
    }

    void PopupOutput::Error(std::string text, const std::source_location& location)
    {
#ifdef _WIN32
        MessageBoxA(window.GetHWND(), ("An error occurred.\n\n" + GetCallerData(location, sourceDir) + ":\n" + text).c_str(), "Error", MB_ICONERROR | MB_OK);
#endif
    }

    void PopupOutput::FatalError(std::string text, const std::source_location& location)
    {
#ifdef _WIN32
        MessageBoxA(window.GetHWND(), ("A fatal error occurred.\n\n" + GetCallerData(location, sourceDir) + ":\n" + text).c_str(), "Fatal Error", MB_ICONERROR | MB_OK);
#endif
    }

    void PopupOutput::InfoGE(std::string text, const std::source_location& location)
    {
#ifdef _WIN32
        MessageBoxA(window.GetHWND(), ("An information from the game engine.\n\n" + GetCallerData(location, sourceDir) + ":\n" + text).c_str(), "Game Engine Information", MB_ICONINFORMATION | MB_OK);
#endif
    }

    void PopupOutput::ErrorGE(std::string text, const std::source_location& location)
    {
#ifdef _WIN32
        MessageBoxA(window.GetHWND(), ("An error occurred in the game engine.\n\n" + GetCallerData(location, sourceDir) + ":\n" + text).c_str(), "Game Engine Error", MB_ICONERROR | MB_OK);
#endif
    }

    void PopupOutput::FatalErrorGE(std::string text, const std::source_location& location)
    {
#ifdef _WIN32
        MessageBoxA(window.GetHWND(), ("A fatal error occurred in the game engine.\n\n" + GetCallerData(location, sourceDir) + ":\n" + text).c_str(), "Game Engine Fatal Error", MB_ICONERROR | MB_OK);
#endif
    }

    void PopupOutput::SDLError(const std::source_location& location)
    {
#ifdef _WIN32
        MessageBoxA(window.GetHWND(), ("An error message from SDL.\n\n" + GetCallerData(location, sourceDir) + ":\n" + std::string(SDL_GetError())).c_str(), "SDL Error", MB_ICONERROR | MB_OK);
#endif
    }

    void PopupOutput::SetLevel(DebugLevel level)
    {
        this->level = level;
    }

    void PopupOutput::SetLevelGE(DebugLevel level)
    {
        this->levelGE = level;
    }
}