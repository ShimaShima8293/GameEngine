#include "animation.h"
#include <vector>

std::vector<AnimationData> dataList;

size_t getAnimationCount()
{
    return dataList.size();
}

void processAnimations()
{
    for (int i = 0; i < dataList.size(); i++)
    {
        AnimationData* currentData = &dataList[i];
        currentData->func(currentData->frame, currentData->len);
        if (currentData->reversed)
        {
            currentData->frame--;
        }
        else
        {
            currentData->frame++;
        }

        if (!currentData->reversed && currentData->frame > currentData->len)
        {
            dataList.erase(dataList.begin() + i);
        }

        if (currentData->reversed && currentData->frame < 0)
        {
            dataList.erase(dataList.begin() + i);
        }
    }
}


void playAnimation(AnimationFunc func, int len, bool reversed)
{
    stopAnimation(func);

    AnimationData newData;
    newData.func = func;
    if (!reversed)
    {
        newData.frame = 0;
    }
    else
    {
        newData.frame = len;
    }
    newData.len = len;
    newData.reversed = reversed;
    dataList.push_back(newData);
}

void stopAnimation(AnimationFunc func)
{
    for (int i = 0; i < dataList.size(); i++)
    {
        if (dataList[i].func == func)
        {
            dataList.erase(dataList.begin() + i);
            i--;
        }
    }
}

void clearAnimations()
{
    dataList.clear();
}