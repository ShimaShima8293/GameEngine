#include "debug.h"

namespace GameEngine
{
    DebugLevel level = PRINT_ERROR;
}
using namespace GameEngine;

void printInfo(std::string text)
{
    if (level <= PRINT_EVERYTHING)
    {
        std::cout << "[INFO]        " << text << "\n";
    }
}

void printError(std::string text)
{
    if (level <= PRINT_ERROR)
    {
        std::cout << "[ERROR]       " << text << "\n";
    }
}

void printFatalError(std::string text)
{
    if (level <= PRINT_FATAL_ERROR)
    {
        std::cout << "[FATAL-ERROR] " << text << "\n";
    }
}

void printSDLError()
{
    if (level <= PRINT_ERROR)
    {
        std::cout << "[SDL-ERROR]   " << SDL_GetError() << "\n";
    }
}

void setDebugLevel(DebugLevel _level)
{
    level = _level;
}