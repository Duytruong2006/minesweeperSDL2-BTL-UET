#include "Timer.h"

LTimer::LTimer ()
{
    // initialize the variables
    mStartTicks = 0;
    mPauseTicks = 0;
    mStarted =  false;
    mPaused = false;
}

void LTimer::start()
{
    // start the timer
    mStarted = true;
    // unpaused the timer
    mPaused = false;
    // get current clock time
    mStartTicks = SDL_GetTicks();
    mPauseTicks = 0;
}
void LTimer::stop()
{
    // stop the timer
    mStarted = false;
    // unpaused the timer
    mPaused = false;
    // clear all the variables
    mStartTicks = 0;
    mPauseTicks = 0;
}
void LTimer::pause()
{
    // when the timer is running and unpausing
    if(mStarted && !mPaused)
    {
        // pause the clock
        mPaused = true;
        //Calculate the paused ticks
        mPauseTicks = SDL_GetTicks() - mStartTicks;
        mStartTicks = 0;
    }
}
Uint32 LTimer::getsTick()
{
    // the actual timer's time
    Uint32 time = 0;
    // when the game is running
    if(mStarted)
    {
        // if it is paused
        if(mPaused)
        {
            //Return the number of ticks when the timer was paused
            time = mPauseTicks;
        }
        // if it is unpaused
        else
        {
            //Return the current time minus the start time
            time = SDL_GetTicks() - mStartTicks;
        }
    }
    return time;
}
bool LTimer::isStarted()
{
    // check if the game  is running or not
    return mStarted;
}

bool LTimer::isPaused()
{
    // check if the game is paused when it is running or not
    return (mStarted && mPaused);
}
