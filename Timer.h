#pragma once
#include <SDL.h>

class LTimer
{
public :
    LTimer();
    void start();
    void stop();
    void pause();
    unsigned int getsTick();
    bool isStarted();
    bool isPaused();
private :
    unsigned int mStartTicks;
    unsigned int mPauseTicks;
    bool mPaused;
    bool mStarted;
};
