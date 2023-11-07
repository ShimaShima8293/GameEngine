#include "debug.h"
#include <iostream>
#include "internal.h"
#include "events.h"
#include "scene.h"

namespace GameEngine
{
    DebugLevel consoleLevel = PRINT_ERROR;
    DebugLevel popupLevel = PRINT_NONE;

    void printInfo(std::string text)
    {
        if (consoleLevel <= PRINT_EVERYTHING)
        {
            std::cout << "[INFO]        " << text << "\n";
        }

        if (popupLevel <= PRINT_EVERYTHING)
        {
            infoPopup("Info message", text);
        }
    }

    void printError(std::string text)
    {
        if (consoleLevel <= PRINT_ERROR)
        {
            std::cout << "[ERROR]       " << text << "\n";
        }

        if (popupLevel <= PRINT_ERROR)
        {
            errorPopup("Error message", (std::string(text) + "\nDo you want to quit the program? (Yes/No)").c_str());
        }
    }

    void printFatalError(std::string text)
    {
        if (consoleLevel <= PRINT_FATAL_ERROR)
        {
            std::cout << "[FATAL-ERROR] " << text << "\n";
        }

        if (popupLevel <= PRINT_FATAL_ERROR)
        {
            errorPopup("Error message", (std::string(text) + "\nDo you want to quit the program? (Yes/No)").c_str());
        }
    }

    void printSDLError()
    {
        if (consoleLevel <= PRINT_ERROR)
        {
            std::cout << "[SDL-ERROR]   " << SDL_GetError() << "\n";
        }

        if (popupLevel <= PRINT_ERROR)
        {
            errorPopup("SDL Error message", (std::string(SDL_GetError()) + "\nDo you want to quit the program? (Yes/No)").c_str());
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

}