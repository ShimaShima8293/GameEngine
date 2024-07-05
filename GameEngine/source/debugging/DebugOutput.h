#pragma once
#include <string>
#include <source_location>

namespace GameEngine
{
    class DebugOutput
    {
    public:
        DebugOutput();

        enum DebugLevel
        {
            DEBUG_LEVEL_EVERYTHING,
            DEBUG_LEVEL_ERROR,
            DEBUG_LEVEL_FATAL_ERROR,
            DEBUG_LEVEL_NONE
        };

        // Output an info message.
        virtual void Info(std::string text, const std::source_location& location = std::source_location::current()) = 0;

        // Output an error message.
        virtual void Error(std::string text, const std::source_location& location = std::source_location::current()) = 0;

        // Output a fatal error message.
        virtual void FatalError(std::string text, const std::source_location& location = std::source_location::current()) = 0;

        // Output an info message.
        virtual void InfoGE(std::string text, const std::source_location& location = std::source_location::current()) = 0;

        // Output an error message.
        virtual void ErrorGE(std::string text, const std::source_location& location = std::source_location::current()) = 0;

        // Output a fatal error message.
        virtual void FatalErrorGE(std::string text, const std::source_location& location = std::source_location::current()) = 0;

        // Output an SDL error message.
        virtual void SDLError(const std::source_location& location = std::source_location::current()) = 0;

        // Set the minimal console output level.
        // \param level Pick from the `DebugLevel` enum.
        virtual void SetLevel(DebugLevel level) = 0;

        // Set the minimal console output level.
        // \param level Pick from the `DebugLevel` enum.
        virtual void SetLevelGE(DebugLevel level) = 0;
    };
}