#include "update.h"
#include "macros.h"
#include <string>
#include <iostream>
#include "scene.h"

void addUpdateDirect(UpdateFunc _func);
void removeUpdateDirect(UpdateFunc _func);

std::vector<UpdateFunc> updateList;

std::vector<UpdateFunc> addQueue;
std::vector<UpdateFunc> removeQueue;

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
    printInfo("Added function at memory address    0x" << _func);
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
            printInfo("Removed function at memory address  0x" << _func);
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
            printInfo("Update function ended at memory address    0x" << updateList[i]);
            updateList.erase(updateList.begin() + i);
            i--;
        }
    }
}