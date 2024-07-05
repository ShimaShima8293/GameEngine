#include "SaveData.h"

#include "debugging/DebugOutput.h"

#include <fstream>

namespace GameEngine
{
    SaveData::SaveData(const std::string path, const std::vector<int> defaultData, bool autoSave, DebugOutput& output) :
        path(path),
        defaultData(defaultData),
        data(),
        autoSave(autoSave),
        output(output)
    {
        this->Load();
    }

    SaveData::~SaveData()
    {
        if (autoSave)
        {
            this->Save();
        }
    }

    void SaveData::SetToDefault()
    {
        data = defaultData;
    }

    int SaveData::GetData(int index)
    {
        if (index < 0)
        {
            output.ErrorGE("SaveData::GetData: Parameter `index` was smaller than 0.");
            return 0;
        }
        if (index >= data.size())
        {
            output.ErrorGE("SaveData::GetData: Parameter `index` was larger than the data size.");
            return 0;
        }

        return data[index];
    }

    std::vector<int> SaveData::GetDataList()
    {
        return data;
    }

    void SaveData::SetData(int index, int value)
    {
        if (index < 0)
        {
            output.ErrorGE("SaveData::GetData: Parameter `index` was smaller than 0.");
            return;
        }
        if (index >= data.size())
        {
            output.ErrorGE("SaveData::GetData: Parameter `index` was larger than the data size.");
            return;
        }

        data[index] = value;
    }

    void SaveData::SetDataList(std::vector<int> list)
    {
        if (list.size() != defaultData.size())
        {
            output.InfoGE("SaveData::SetDataList: Parameter `list`'s size was not equal to the default data size.");
            return;
        }
        data = list;
    }

    void SaveData::Save()
    {
        std::ofstream file(path);
        if (!file.is_open())
        {
            output.ErrorGE("saveData: Failed to open " + path);
            return;
        }

        std::string separator = ",";

        std::string output;
        for (int i = 0; i < data.size(); i++)
        {
            output.append(std::to_string(data[i]));

            if (i != data.size() - 1)
            {
                output.append(separator);
            }
        }

        file << output;
        file.close();
    }

    void SaveData::Load()
    {
        std::ifstream file(path);
        if (!file.is_open())
        {
            output.InfoGE("LoadData: Couldn't open file: " + path);
        }

        std::vector<int> result;

        std::string line;
        while (std::getline(file, line))
        {
            std::string separator = ",";
            size_t separator_length = separator.length();

            size_t offset = 0;
            while (true)
            {
                size_t pos = line.find(separator, offset);

                if (pos == std::string::npos)
                {
                    try
                    {
                        result.push_back(std::stoi(line.substr(offset)));
                    }
                    catch (const std::invalid_argument&)
                    {
                        output.ErrorGE("SaveData::Load: Invalid data.");
                        file.close();
                    }
                    break;
                }

                try
                {
                    result.push_back(std::stoi(line.substr(offset, pos - offset)));
                }
                catch (const std::invalid_argument&)
                {
                    output.ErrorGE("SaveData::Load: Invalid data.");
                    file.close();
                }

                offset = pos + separator_length;
            }

        }
        file.close();
        this->data = result;

        if (data.size() != defaultData.size())
        {
            output.InfoGE("SaveData::Load: Failed to Load data at " + path);
            data = defaultData;
        }
    }
}
