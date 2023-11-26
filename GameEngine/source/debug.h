#pragma once
#include <string>

namespace GameEngine
{

    // Used by `setDebugLevel()`
    enum DebugLevel
    {
        DEBUG_LEVEL_EVERYTHING,
        DEBUG_LEVEL_ERROR,
        DEBUG_LEVEL_FATAL_ERROR,
        DEBUG_LEVEL_NONE
    };

    // Print an info message to the console.
    void printInfo(std::string text);

    // Print an error message to the console.
    void printError(std::string text);

    // Print a fatal error message to the console.
    void printFatalError(std::string text);

    // Print an info message to the console.
    void printInfoGE(std::string text);

    // Print an error message to the console.
    void printErrorGE(std::string text);

    // Print a fatal error message to the console.
    void printFatalErrorGE(std::string text);

    // Print an SDL error message to the console.
    void printSDLError();

    void errorPopup(std::string title, std::string text);

    void infoPopup(std::string title, std::string text);

    // Set the minimal console output level.
    // \param _level Pick from the `DebugLevel` enum.
    void setConsoleLogLevel(DebugLevel _level);

    // Set the minimal popup output level.
    // \param _level Pick from the `DebugLevel` enum.
    void setPopupLogLevel(DebugLevel _level);

    // Set the minimal console output level.
    // \param _level Pick from the `DebugLevel` enum.
    void setConsoleLogLevelGE(DebugLevel _level);

    // Set the minimal popup output level.
    // \param _level Pick from the `DebugLevel` enum.
    void setPopupLogLevelGE(DebugLevel _level);

}