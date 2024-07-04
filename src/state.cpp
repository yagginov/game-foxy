#include "state.h"

State::State(double max_time) :
    time(0), maxTime(max_time), isStart(true)
{}

bool State::is_start()
{
    if (isStart)
    {
        isStart = false;
        return true;
    }
    return false;
}

bool State::update(double delta)
{
    time += delta;

    if (time > maxTime)
    {
        return true;
    }
    return false;
}

void State::reset()
{
    time = 0;
    isStart = true;
}
