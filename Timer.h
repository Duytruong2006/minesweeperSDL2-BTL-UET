#pragma once
#include <SDL.h>

class LTimer
{
public :
    LTimer();
    // start the timer
    void start();
    // stop the timer
    void stop();
    // pause the timer
    void pause();
    // gets the timer's time
    Uint32 getTicks();
    // check the timer status
    bool isStarted();
    bool isPaused();
private :
    // the clock time when the timer started
    Uint32 mStartTicks;
    // the clock time when the timer stopped
    Uint32 mPauseTicks;
    // the timer status
    bool mPaused;
    bool mStarted;
};

