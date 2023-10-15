#pragma once
#include <string>

enum DebugLevel
{
    PRINT_EVERYTHING,
    PRINT_ERROR,
    PRINT_FATAL_ERROR,
    PRINT_NONE
};

void printInfo(std::string text);

void printError(std::string text);

void printFatalError(std::string text);

void printSDLError();

void setDebugLevel(DebugLevel _level);