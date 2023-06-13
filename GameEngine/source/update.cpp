#include "update.h"
#include "macros.h"
#include <string>
#include <iostream>
#include "scene.h"

bool addUpdateDirect(UpdateFunc _func, bool replace = true);
bool removeUpdateDirect(UpdateFunc _func);

std::vector<int (*)()> updateList;

std::vector<int (*)()> addQueue;
std::vector<int (*)()> removeQueue;

std::map<int (*)(), UpdateData> dataList;

size_t getUpdateCount()
{
    return updateList.size();
}
void addUpdate(UpdateFunc _func)
{
    addQueue.push_back(_func);
}
void removeUpdate(UpdateFunc _func)
{
    removeQueue.push_back(_func);
}
void clearUpdates()
{
    addQueue.clear();
    removeQueue.clear();
    updateList.clear();

}
bool addUpdateDirect(UpdateFunc _func, bool replace)
{
    printInfo("Added function at memory address    0x" << _func);
    bool returnVal = false;
    for (int i = 0; i < updateList.size(); i++)
    {

        if (updateList[i] == _func)
        {
            returnVal = true;
            //printInfo("Found matching function!");
            if (replace)
            {
                updateList.erase(updateList.begin() + i);
                i--;
            }
        }
    }
    if (replace || !returnVal)
    {
        updateList.push_back(_func);
    }

    return returnVal;
}
bool removeUpdateDirect(UpdateFunc _func)
{
    printInfo("Removed function at memory address  0x" << _func);
    bool returnVal = false;
    for (int i = 0; i < updateList.size(); i++)
    {

        if (updateList[i] == _func)
        {
            printInfo("Found matching function!");
            updateList.erase(updateList.begin() + i);
            returnVal = true;
        }
    }
    return returnVal;
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

    if (getCurrentScene() != nullptr)
        getCurrentScene()->update();

    for (int i = 0; i < updateList.size(); i++)
    {
        if (updateList[i]() != UPDATE_CONTINUE)
        {
            printInfo("Ended function at memory address    0x" << updateList[i]);
            updateList.erase(updateList.begin() + i);
            i--;
        }
    }
}
void createUpdate(UpdateFunc _func, int len, int* frame)
{
    resetUpdate(_func);
    dataList[_func].len = len;
    dataList[_func].enabled = true;
    frame = &dataList[_func].frame;
}
void resetUpdate(UpdateFunc _func)
{
    dataList[_func].enabled = false;
    dataList[_func].frame = 0;
}
UpdateData getUpdateData(UpdateFunc _func)
{
    return dataList[_func];
}