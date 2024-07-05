#include "callerData.h"

#include <filesystem>

namespace GameEngine
{
    std::string GetCallerData(const std::source_location& location, const std::filesystem::path& sourceDir)
    {
        return std::filesystem::relative(std::filesystem::path(location.file_name()), sourceDir).string() + ":" + std::to_string(location.line());
    }
}