#include "Timer.h"

LTimer::LTimer ()
{
    mStartTicks = 0;
    mPauseTicks = 0;
    mStarted =  false;
    mPaused = false;
}

void LTimer::start()
{
    mStarted = true;
    mPaused = false;
    mStartTicks = SDL_GetTicks();
    mPauseTicks = 0;
}
void LTimer::stop()
{
    mStarted = false;
    mPaused = false;
    mStartTicks = 0;
    mPauseTicks = 0;
}
void LTimer::pause()
{
    if(mStarted && !mPaused)
    {
        mPaused = true;
        mPauseTicks = SDL_GetTicks() - mStartTicks;
        mStartTicks = 0;
    }
}
Uint32 LTimer::getTicks()
{
    Uint32 time = 0;
    if(mStarted)
    {
        if(mPaused)
        {
            time = mPauseTicks;
        }
        else
        {
            time = SDL_GetTicks() - mStartTicks;
        }
    }
    return time;
}
bool LTimer::isStarted()
{
    return mStarted;
}

bool LTimer::isPaused()
{
    return (mStarted && mPaused);
}
