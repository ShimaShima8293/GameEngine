#include "ConsoleOutput.h"
#include "callerData.h"

#include <SDL.h>

#include <iostream>
#include <filesystem>

namespace GameEngine
{
    ConsoleOutput::ConsoleOutput(const std::filesystem::path& sourceDir) :
        ConsoleOutput(DebugOutput::DEBUG_LEVEL_ERROR, DebugOutput::DEBUG_LEVEL_ERROR, sourceDir)
    {
    }

    ConsoleOutput::ConsoleOutput(DebugLevel level, DebugLevel levelGE, const std::filesystem::path& sourceDir) :
        level(level),
        levelGE(levelGE),
        sourceDir(sourceDir)
    {
        
    }

    void ConsoleOutput::Info(std::string text, const std::source_location& location)
    {
        if (level <= DEBUG_LEVEL_EVERYTHING)
        {
            std::cout << "[INFO]           " << GetCallerData(location, sourceDir) << ": " << text << "\n";
        }
    }

    void ConsoleOutput::Error(std::string text, const std::source_location& location)
    {
        if (level <= DEBUG_LEVEL_ERROR)
        {
            std::cout << "[ERROR]          " << GetCallerData(location, sourceDir) << ": " << text << "\n";
        }
    }

    void ConsoleOutput::FatalError(std::string text, const std::source_location& location)
    {
        if (level <= DEBUG_LEVEL_FATAL_ERROR)
        {
            std::cout << "[FATAL-ERROR]    " << GetCallerData(location, sourceDir) << ": " << text << "\n";
        }
    }

    void ConsoleOutput::InfoGE(std::string text, const std::source_location& location)
    {
        if (levelGE <= DEBUG_LEVEL_EVERYTHING)
        {
            std::cout << "[GE-INFO]        " << GetCallerData(location, sourceDir) << ": " << text << "\n";
        }
    }

    void ConsoleOutput::ErrorGE(std::string text, const std::source_location& location)
    {
        if (levelGE <= DEBUG_LEVEL_ERROR)
        {
            std::cout << "[GE-ERROR]       " << GetCallerData(location, sourceDir) << ": " << text << "\n";
        }
    }

    void ConsoleOutput::FatalErrorGE(std::string text, const std::source_location& location)
    {
        if (levelGE <= DEBUG_LEVEL_FATAL_ERROR)
        {
            std::cout << "[GE-FATAL-ERROR] " << GetCallerData(location, sourceDir) << ": " << text << "\n";
        }
    }

    void ConsoleOutput::SDLError(const std::source_location& location)
    {
        if (level <= DEBUG_LEVEL_ERROR)
        {
            std::cout << "[SDL-ERROR]      " << GetCallerData(location, sourceDir) << ": " << SDL_GetError() << "\n";
        }
    }

    void ConsoleOutput::SetLevel(DebugLevel level)
    {
        this->level = level;
    }

    void ConsoleOutput::SetLevelGE(DebugLevel level)
    {
        this->levelGE = level;
    }
}