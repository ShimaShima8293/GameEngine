#include "animation.h"
#include "macros.h"
#include "utilities.h"
#include <vector>

namespace GameEngine
{
    std::vector<AnimationData> dataList;
    std::vector<AnimationData> playQueue;
    std::vector<AnimationFunc> stopQueue;

    std::vector<EntityAnimationData> dataList2;
    std::vector<EntityAnimationData> playQueue2;
    std::vector<EntityAnimationFunc> stopQueue2;

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

    for (int i = 0; i < playQueue2.size(); i++)
    {
        dataList2.push_back(playQueue2[i]);
    }
    playQueue2.clear();

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

    for (int i = 0; i < stopQueue2.size(); i++)
    {
        for (int j = 0; j < dataList2.size(); j++)
        {
            if (dataList2[j].func == stopQueue2[i])
            {
                dataList2.erase(dataList2.begin() + j);
                j--;
            }
        }
    }
    stopQueue2.clear();

    for (int i = 0; i < dataList.size(); i++)
    {
        AnimationData* currentData = &dataList[i];
        if (currentData->func == nullptr)
        {
            printError("processAnimations: currentData->func was nullptr");
            continue;
        }

        int result = currentData->func(currentData->frame, currentData->len);
        if (currentData->reversed)
        {
            currentData->frame--;
        }
        else
        {
            currentData->frame++; 
        }

        bool remove = false;
        if (currentData->len > 0)
        {
            if (!currentData->reversed)
            {
                if (currentData->frame > currentData->len)
                {
                    remove = true;
                }
            }
            else
            {
                if (currentData->reversed && currentData->frame < 0)
                {
                    remove = true;
                }
            }
        }
        if (result != 0)
        {
            remove = true;
        }
        if (remove)
        {
            dataList.erase(dataList.begin() + i);
            i--;
        }
    }

    for (int i = 0; i < dataList2.size(); i++)
    {
        EntityAnimationData* currentData = &dataList2[i];
        if (currentData->func == nullptr)
        {
            printError("processAnimations: currentData->func was nullptr");
            continue;
        }

        int result = currentData->func(currentData->entity, currentData->frame, currentData->len);
        if (currentData->reversed)
        {
            currentData->frame--;
        }
        else
        {
            currentData->frame++;
        }

        bool remove = false;
        if (currentData->len > 0)
        {
            if (!currentData->reversed)
            {
                if (currentData->frame > currentData->len)
                {
                    remove = true;
                }
            }
            else
            {
                if (currentData->reversed && currentData->frame < 0)
                {
                    remove = true;
                }
            }
        }
        if (result != 0)
        {
            remove = true;
        }
        if (remove)
        {
            dataList2.erase(dataList2.begin() + i);
            i--;
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

    if (len < 0)
    {
        printError("playAnimation: len cannot be smaller than 0.");
        return;
    }

    if (len == 0 && reversed)
    {
        printError("playAnimation: animation cannot be reversed when len is 0.");
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

    AnimationData newData = {};
    newData.func = func;
    if (!reversed)
    {
        newData.frame = 0;
    }
    else
    {
        newData.frame = roundToInt(len * animationSpeed);
    }
    newData.len = roundToInt(len * animationSpeed);
    newData.reversed = reversed;
    playQueue.push_back(newData);
}

void playEntityAnimation(Entity* entity, EntityAnimationFunc func, int len, bool reversed)
{
    if (func == nullptr)
    {
        printError("playEntityAnimation: parameter func was nullptr.");
        return;
    }

    if (len < 0)
    {
        printError("playEntityAnimation: len cannot be smaller than 0.");
        return;
    }

    if (len == 0 && reversed)
    {
        printError("playEntityAnimation: animation cannot be reversed when len is 0.");
        return;
    }

    for (int i = 0; i < dataList2.size(); i++)
    {
        if (dataList2[i].func == func)
        {
            dataList2.erase(dataList2.begin() + i);
            i--;
        }
    }

    EntityAnimationData newData = {};
    newData.func = func;
    if (!reversed)
    {
        newData.frame = 0;
    }
    else
    {
        newData.frame = roundToInt(len * animationSpeed);
    }
    newData.len = roundToInt(len * animationSpeed);
    newData.reversed = reversed;
    newData.entity = entity;
    playQueue2.push_back(newData);
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

void stopEntityAnimation(EntityAnimationFunc func)
{
    if (func == nullptr)
    {
        printError("stopEntityAnimation: parameter func was nullptr.");
        return;
    }

    stopQueue2.push_back(func);
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