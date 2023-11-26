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

    void printInfo(std::string text)
    {
        if (consoleLevel <= DEBUG_LEVEL_EVERYTHING)
        {
            std::cout << "[INFO]           " << text << "\n";
        }

        if (popupLevel <= DEBUG_LEVEL_EVERYTHING)
        {
            infoPopup("Info Message", text);
        }
    }

    void printError(std::string text)
    {
        if (consoleLevel <= DEBUG_LEVEL_ERROR)
        {
            std::cout << "[ERROR]          " << text << "\n";
        }

        if (popupLevel <= DEBUG_LEVEL_ERROR)
        {
            errorPopup("Error Message", (std::string(text) + "\nDo you want to quit the program? (Yes/No)").c_str());
        }
    }

    void printFatalError(std::string text)
    {
        if (consoleLevel <= DEBUG_LEVEL_FATAL_ERROR)
        {
            std::cout << "[FATAL-ERROR]    " << text << "\n";
        }

        if (popupLevel <= DEBUG_LEVEL_FATAL_ERROR)
        {
            errorPopup("Error Message", (std::string(text) + "\nDo you want to quit the program? (Yes/No)").c_str());
        }
    }

    void printInfoGE(std::string text)
    {
        if (consoleLevelGE <= DEBUG_LEVEL_EVERYTHING)
        {
            std::cout << "[GE-INFO]        " << text << "\n";
        }

        if (popupLevelGE <= DEBUG_LEVEL_EVERYTHING)
        {
            infoPopup("GameEngine Info Message", text);
        }
    }

    void printErrorGE(std::string text)
    {
        if (consoleLevelGE <= DEBUG_LEVEL_ERROR)
        {
            std::cout << "[GE-ERROR]       " << text << "\n";
        }

        if (popupLevelGE <= DEBUG_LEVEL_ERROR)
        {
            errorPopup("GameEngine Error Message", (std::string(text) + "\nDo you want to quit the program? (Yes/No)").c_str());
        }
    }

    void printFatalErrorGE(std::string text)
    {
        if (consoleLevelGE <= DEBUG_LEVEL_FATAL_ERROR)
        {
            std::cout << "[GE-FATAL-ERROR] " << text << "\n";
        }

        if (popupLevelGE <= DEBUG_LEVEL_FATAL_ERROR)
        {
            errorPopup("GameEngine Fatal Error Message", (std::string(text) + "\nDo you want to quit the program? (Yes/No)").c_str());
        }
    }

    void printSDLError()
    {
        if (consoleLevel <= DEBUG_LEVEL_ERROR)
        {
            std::cout << "[SDL-ERROR]      " << SDL_GetError() << "\n";
        }

        if (popupLevel <= DEBUG_LEVEL_ERROR)
        {
            errorPopup("SDL Error Message", (std::string(SDL_GetError()) + "\nDo you want to quit the program? (Yes/No)").c_str());
        }
    }

    void errorPopup(std::string title, std::string text)
    {
#ifdef _WIN32
        if (MessageBoxA(getHWND(), text.c_str(), title.c_str(), MB_ICONERROR | MB_YESNO) == IDYES)
        {
            endMainloop();
        }
#endif
    }

    void infoPopup(std::string title, std::string text)
    {
#ifdef _WIN32
        MessageBoxA(getHWND(), text.c_str(), title.c_str(), MB_ICONINFORMATION | MB_OK);
#endif
    }

    void setConsoleLogLevel(DebugLevel _level)
    {
        consoleLevel = _level;
    }

    void setPopupLogLevel(DebugLevel _level)
    {
        popupLevel = _level;
    }

    void setConsoleLogLevelGE(DebugLevel _level)
    {
        consoleLevelGE = _level;
    }

    void setPopupLogLevelGE(DebugLevel _level)
    {
        popupLevelGE = _level;
    }
}