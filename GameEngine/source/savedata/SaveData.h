#pragma once

#include "internal.h"

#include <vector>
#include <string>

namespace GameEngine
{
    class DebugOutput;

    class SaveData
    {
    public:
        SaveData(const std::string path, const std::vector<int> defaultData, bool autoSave, DebugOutput& output);

        ~SaveData();

        void SetToDefault();

        void Load();

        int GetData(int index);

        std::vector<int> GetDataList();

        void SetData(int index, int value);

        void SetDataList(std::vector<int> list);

        void Save();

    private:
        const std::string path;

        std::vector<int> data;

        const std::vector<int> defaultData;

        bool autoSave;

        DebugOutput& output;
    };
}
