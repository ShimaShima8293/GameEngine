#include "update.h"
#include "macros.h"
#include <string>
#include <iostream>
#include "scene.h"

void addUpdateDirect(UpdateFunc _func);
void removeUpdateDirect(UpdateFunc _func);

namespace GameEngine
{
    std::vector<UpdateFunc> updateList{};

    std::vector<UpdateFunc> addQueue{};
    std::vector<UpdateFunc> removeQueue{};
}
using namespace GameEngine;

size_t getUpdateCount()
{
    return updateList.size();
}

void addUpdate(UpdateFunc _func)
{
    if (_func == nullptr)
    {
        printError("addUpdate: parameter func was nullptr.");
        return;
    }
    addQueue.push_back(_func);
}

void removeUpdate(UpdateFunc _func)
{
    if (_func == nullptr)
    {
        printError("removeUpdate: parameter func was nullptr.");
        return;
    }
    removeQueue.push_back(_func);
}

void clearUpdates()
{
    addQueue.clear();
    removeQueue.clear();
    updateList.clear();
}

void addUpdateDirect(UpdateFunc _func)
{
    if (_func == nullptr)
    {
        printError("addUpdateDirect: parameter func was nullptr.");
        return;
    }

    removeUpdateDirect(_func);
    updateList.push_back(_func);
}

void removeUpdateDirect(UpdateFunc _func)
{
    if (_func == nullptr)
    {
        printError("removeUpdateDirect: parameter func was nullptr.");
        return;
    }
    for (int i = 0; i < updateList.size(); i++)
    {
        if (updateList[i] == _func)
        {
            updateList.erase(updateList.begin() + i);
        }
    }
}

void processUpdates()
{
    for (int i = 0; i < addQueue.size(); i++)
    {
        addUpdateDirect(addQueue[i]);
    }
    for (int i = 0; i < removeQueue.size(); i++)
    {
        removeUpdateDirect(removeQueue[i]);
    }

    addQueue.clear();
    removeQueue.clear();

    for (int i = 0; i < updateList.size(); i++)
    {
        if (updateList[i]() != UPDATE_CONTINUE)
        {
            updateList.erase(updateList.begin() + i);
            i--;
        }
    }
}