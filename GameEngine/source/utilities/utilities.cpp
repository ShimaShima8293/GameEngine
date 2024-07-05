#include "utilities.h"
#include "internal.h"
#include <cmath>

namespace GameEngine
{
    float CheckDistance(Vec2 a, Vec2 b)
    {
        return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
    }

    float GetAngleBetween(Vec2 a, Vec2 b)
    {
        return 90.0f - atan2(b.y - a.y, b.x - a.x) * (180.0f / 3.14f);
    }

    std::vector<std::string> Split(std::string input, std::string separator)
    {
        size_t separator_length = separator.length();

        std::vector<std::string> list;

        size_t offset = 0;
        while (true)
        {
            size_t pos = input.find(separator, offset);

            if (pos == std::string::npos)
            {
                list.push_back(input.substr(offset));

                break;
            }
            else
            {
                list.push_back(input.substr(offset, pos - offset));
            }
            offset = pos + separator_length;

        }
        return list;
    }

    Vec2 GetCenterPos(Rect rect)
    {
        return { rect.x + (rect.w / 2.0f), rect.y + (rect.h / 2.0f) };
    }

    void PauseConsole()
    {
#ifdef _WIN32
        system("pause");
#else
        std::cout << "Press enter key to exit." << std::endl;
        std::Getchar();
#endif
    }
}