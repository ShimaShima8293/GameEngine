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
        currentData->frame++;
        if (currentData->frame > currentData->len)
        {
            dataList.erase(dataList.begin() + i);
        }
    }
}


void playAnimation(AnimationFunc func, int len)
{
    stopAnimation(func);

    AnimationData newData;
    newData.func = func;
    newData.len = len;
    newData.frame = 0;
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