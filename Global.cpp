#include "raylib.h"
#include "raymath.h"
#include "Global.hpp"
#include <deque>

using namespace std;

bool Global::EventTriggered(double interval)
{
    double currentTime = GetTime();

    if(currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

bool Global::ElementInDeque(Vector2 element, deque<Vector2> deque)
{
    for (unsigned int i = 0; i < deque.size(); i++)
        if(Vector2Equals(deque[i], element))
            return true;
    return false;
}