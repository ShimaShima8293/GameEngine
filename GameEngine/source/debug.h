#pragma once
#include <string>

// Used by `setDebugLevel()`
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

// Set the minimal console output level.
// \param _level Pick from the `DebugLevel` enum.
void setDebugLevel(DebugLevel _level);