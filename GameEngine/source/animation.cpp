#include "animation.h"
#include "macros.h"
#include "utilities.h"
#include <vector>

namespace GameEngine
{
    std::vector<AnimationData> dataList;
    std::vector<AnimationData> playQueue;
    std::vector<AnimationFunc> stopQueue;
    float animationSpeed = 1.0f;
}
using namespace GameEngine;

size_t getAnimationCount()
{
    return dataList.size();
}

void processAnimations()
{
    for (int i = 0; i < playQueue.size(); i++)
    {
        dataList.push_back(playQueue[i]);
    }
    playQueue.clear();

    for (int i = 0; i < stopQueue.size(); i++)
    {
        for (int j = 0; j < dataList.size(); j++)
        {
            if (dataList[j].func == stopQueue[i])
            {
                dataList.erase(dataList.begin() + j);
                j--;
            }
        }
    }
    stopQueue.clear();

    for (int i = 0; i < dataList.size(); i++)
    {
        AnimationData* currentData = &dataList[i];
        if (currentData->func == nullptr)
        {
            printError("processAnimations: currentData->func was nullptr");
            continue;
        }

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
    if (func == nullptr)
    {
        printError("playAnimation: parameter func was nullptr.");
        return;
    }

    for (int i = 0; i < dataList.size(); i++)
    {
        if (dataList[i].func == func)
        {
            dataList.erase(dataList.begin() + i);
            i--;
        }
    }

    AnimationData newData;
    newData.func = func;
    if (!reversed)
    {
        newData.frame = 0;
    }
    else
    {
        newData.frame = len * animationSpeed;
    }
    newData.len = roundToInt(len * animationSpeed);
    newData.reversed = reversed;
    playQueue.push_back(newData);
}

void stopAnimation(AnimationFunc func)
{
    if (func == nullptr)
    {
        printError("stopAnimation: parameter func was nullptr.");
        return;
    }

    stopQueue.push_back(func);


}

void clearAnimations()
{
    dataList.clear();
}

void setGlobalAnimationSpeed(float speed)
{
    animationSpeed = speed;
}

float getGlobalAnimationSpeed()
{
    return animationSpeed;
}