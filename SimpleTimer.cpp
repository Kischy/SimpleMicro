#include "SimpleTimer.h"

namespace ck
{

SimpleTimer::SimpleTimer(unsigned long (*getTime)(), void (*timeOutCallback)())
{
    this->getTime = getTime;
    this->timeOutCallback = timeOutCallback;
}


void SimpleTimer::start(unsigned long timeToTimeout)
{
    this->timeToTimeout = timeToTimeout;
    timerIsRunning = true;
    setLastTimeoutToNow();    
}

void SimpleTimer::stop() 
{
    timerIsRunning = false;
}

bool SimpleTimer::isTimerRunning() const
{
    return timerIsRunning;
}

void SimpleTimer::checkForTimeout() 
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


void SimpleTimer::doTimeout() 
{
    if(timeOutCallback != nullptr)
    {
        timeOutCallback();
    }

    setLastTimeoutToNow();
}

bool SimpleTimer::isATimeout() const
{
    return ( getTime() - lastTimeout > timeToTimeout );
}


void SimpleTimer::setLastTimeoutToNow()
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

