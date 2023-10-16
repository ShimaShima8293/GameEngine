#pragma once
#include <string>

enum DebugLevel
{
    PRINT_EVERYTHING,
    PRINT_ERROR,
    PRINT_FATAL_ERROR,
    PRINT_NONE
};

// Print an info message to the console.
void printInfo(std::string text);

// Print an error message to the console.
void printError(std::string text);

// Print a fatal error message to the console.
void printFatalError(std::string text);

// Print an SDL error message to the console.
void printSDLError();

void setDebugLevel(DebugLevel _level);