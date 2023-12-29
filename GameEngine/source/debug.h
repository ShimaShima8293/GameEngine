#pragma once
#include <string>

namespace GameEngine
{

    // Used by `SetDebugLevel()`
    enum DebugLevel
    {
        DEBUG_LEVEL_EVERYTHING,
        DEBUG_LEVEL_ERROR,
        DEBUG_LEVEL_FATAL_ERROR,
        DEBUG_LEVEL_NONE
    };

    // Print an info message to the console.
    void PrintInfo(std::string text);

    // Print an error message to the console.
    void PrintError(std::string text);

    // Print a fatal error message to the console.
    void PrintFatalError(std::string text);

    // Print an info message to the console.
    void PrintInfoGE(std::string text);

    // Print an error message to the console.
    void PrintErrorGE(std::string text);

    // Print a fatal error message to the console.
    void PrintFatalErrorGE(std::string text);

    // Print an SDL error message to the console.
    void PrintSDLError();

    void ErrorPopup(std::string title, std::string text);

    void InfoPopup(std::string title, std::string text);

    // Set the minimal console output level.
    // \param _level Pick from the `DebugLevel` enum.
    void SetConsoleLogLevel(DebugLevel _level);

    // Set the minimal popup output level.
    // \param _level Pick from the `DebugLevel` enum.
    void SetPopupLogLevel(DebugLevel _level);

    // Set the minimal console output level.
    // \param _level Pick from the `DebugLevel` enum.
    void SetConsoleLogLevelGE(DebugLevel _level);

    // Set the minimal popup output level.
    // \param _level Pick from the `DebugLevel` enum.
    void SetPopupLogLevelGE(DebugLevel _level);

}