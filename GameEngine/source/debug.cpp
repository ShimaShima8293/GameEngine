#include "debug.h"

void printInfo(std::string text)
{
    std::cout << "[INFO]        " << text << "\n";
    //std::cout << text << std::endl;
}

void printError(std::string text)
{
    std::cout << "[ERROR]       " << text << "\n";
}

void printFatalError(std::string text)
{
    std::cout << "[FATAL-ERROR] " << text << "\n";
}

void printSDLError()
{
    std::cout << "[SDL-ERROR]   " << SDL_GetError() << "\n";
}