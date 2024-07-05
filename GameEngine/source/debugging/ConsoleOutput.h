#pragma once
#include "DebugOutput.h"
#include <source_location>
#include <filesystem>

namespace GameEngine
{
    class ConsoleOutput : public DebugOutput
    {
    public:
        ConsoleOutput(const std::filesystem::path& sourceDir);

        ConsoleOutput(DebugLevel level, DebugLevel levelGE, const std::filesystem::path& sourceDir);

        void Info(std::string text, const std::source_location& location = std::source_location::current());

        void Error(std::string text, const std::source_location& location = std::source_location::current());

        void FatalError(std::string text, const std::source_location& location = std::source_location::current());

        void InfoGE(std::string text, const std::source_location& location = std::source_location::current());

        void ErrorGE(std::string text, const std::source_location& location = std::source_location::current());

        void FatalErrorGE(std::string text, const std::source_location& location = std::source_location::current());

        void SDLError(const std::source_location& location = std::source_location::current());

        void SetLevel(DebugLevel level);

        void SetLevelGE(DebugLevel level);
    private:

        DebugLevel level;
        DebugLevel levelGE;

        const std::filesystem::path sourceDir;
    };
}