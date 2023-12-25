#include "debug.h"
#include <iostream>
#include "internal.h"
#include "events.h"
#include "scene.h"

namespace GameEngine
{
    DebugLevel consoleLevel = DEBUG_LEVEL_EVERYTHING;
    DebugLevel popupLevel = DEBUG_LEVEL_FATAL_ERROR;

    DebugLevel consoleLevelGE = DEBUG_LEVEL_EVERYTHING;
    DebugLevel popupLevelGE = DEBUG_LEVEL_FATAL_ERROR;

    void PrintInfo(std::string text)
    {
        if (consoleLevel <= DEBUG_LEVEL_EVERYTHING)
        {
            std::cout << "[INFO]           " << text << "\n";
        }

        if (popupLevel <= DEBUG_LEVEL_EVERYTHING)
        {
            InfoPopup("Info Message", text);
        }
    }

    void PrintError(std::string text)
    {
        if (consoleLevel <= DEBUG_LEVEL_ERROR)
        {
            std::cout << "[ERROR]          " << text << "\n";
        }

        if (popupLevel <= DEBUG_LEVEL_ERROR)
        {
            ErrorPopup("Error Message", (std::string(text) + "\nDo you want to quit the program? (Yes/No)").c_str());
        }
    }

    void PrintFatalError(std::string text)
    {
        if (consoleLevel <= DEBUG_LEVEL_FATAL_ERROR)
        {
            std::cout << "[FATAL-ERROR]    " << text << "\n";
        }

        if (popupLevel <= DEBUG_LEVEL_FATAL_ERROR)
        {
            ErrorPopup("Error Message", (std::string(text) + "\nDo you want to quit the program? (Yes/No)").c_str());
        }
    }

    void PrintInfoInternal(std::string text)
    {
        if (consoleLevelGE <= DEBUG_LEVEL_EVERYTHING)
        {
            std::cout << "[GE-INFO]        " << text << "\n";
        }

        if (popupLevelGE <= DEBUG_LEVEL_EVERYTHING)
        {
            InfoPopup("GameEngine Info Message", text);
        }
    }

    void PrintErrorInternal(std::string text)
    {
        if (consoleLevelGE <= DEBUG_LEVEL_ERROR)
        {
            std::cout << "[GE-ERROR]       " << text << "\n";
        }

        if (popupLevelGE <= DEBUG_LEVEL_ERROR)
        {
            ErrorPopup("GameEngine Error Message", (std::string(text) + "\nDo you want to quit the program? (Yes/No)").c_str());
        }
    }

    void PrintFatalErrorInternal(std::string text)
    {
        if (consoleLevelGE <= DEBUG_LEVEL_FATAL_ERROR)
        {
            std::cout << "[GE-FATAL-ERROR] " << text << "\n";
        }

        if (popupLevelGE <= DEBUG_LEVEL_FATAL_ERROR)
        {
            ErrorPopup("GameEngine Fatal Error Message", (std::string(text) + "\nDo you want to quit the program? (Yes/No)").c_str());
        }
    }

    void PrintSDLError()
    {
        if (consoleLevel <= DEBUG_LEVEL_ERROR)
        {
            std::cout << "[SDL-ERROR]      " << SDL_GetError() << "\n";
        }

        if (popupLevel <= DEBUG_LEVEL_ERROR)
        {
            ErrorPopup("SDL Error Message", (std::string(SDL_GetError()) + "\nDo you want to quit the program? (Yes/No)").c_str());
        }
    }

    void ErrorPopup(std::string title, std::string text)
    {
#ifdef _WIN32
        if (MessageBoxA(nullptr, text.c_str(), title.c_str(), MB_ICONERROR | MB_YESNO) == IDYES)
        {
            //endMainloop();
            exit(-1);
        }
#endif
    }

    void InfoPopup(std::string title, std::string text)
    {
#ifdef _WIN32
        MessageBoxA(nullptr, text.c_str(), title.c_str(), MB_ICONINFORMATION | MB_OK);
#endif
    }

    void SetConsoleLogLevel(DebugLevel _level)
    {
        consoleLevel = _level;
    }

    void SetPopupLogLevel(DebugLevel _level)
    {
        popupLevel = _level;
    }

    void SetConsoleLogLevelGE(DebugLevel _level)
    {
        consoleLevelGE = _level;
    }

    void SetPopupLogLevelGE(DebugLevel _level)
    {
        popupLevelGE = _level;
    }
}