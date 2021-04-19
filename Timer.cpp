#include "Timer.h"

namespace smpmcr
{

Timer::Timer(unsigned long (*getTime)(), void (*timeOutCallback)())
{
    this->getTime = getTime;
    this->timeOutCallback = timeOutCallback;
}


void Timer::start(unsigned long timeToTimeout)
{
    this->timeToTimeout = timeToTimeout;
    timerIsRunning = true;
    setLastTimeoutToNow();    
}

void Timer::stop() 
{
    timerIsRunning = false;
}

bool Timer::isTimerRunning() const
{
    return timerIsRunning;
}

void Timer::checkForTimeout() 
{
    if(timerIsRunning)
    {
        if(getTime == nullptr)
        {
            doTimeout();
        }
        else
        {
            if(isATimeout())
            {
                doTimeout();
            }             
        }
        
    }
}


void Timer::doTimeout() 
{
    if(timeOutCallback != nullptr)
    {
        timeOutCallback();
    }

    setLastTimeoutToNow();
}

bool Timer::isATimeout() const
{
    return ( getTime() - lastTimeout > timeToTimeout );
}


void Timer::setLastTimeoutToNow()
{
    if(getTime != nullptr)
    {
        lastTimeout = getTime();
    }
    else
    {
        lastTimeout = 0;
    }
}


}

