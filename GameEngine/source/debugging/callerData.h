#pragma once

#include "internal.h"

#include <string>
#include <source_location>
#include <filesystem>

namespace GameEngine
{
    std::string GetCallerData(const std::source_location& location, const std::filesystem::path& sourceDir);
}