#include "Timer.h"

namespace smpmcr
{

Timer::Timer(unsigned long (*getTime)(), void (*timeoutCallback)()) : Event(timeoutCallback)
{
    setTimeFunction(getTime);
}


void Timer::setTimeFunction(unsigned long (*getTime)())
{
    m_getTime = getTime;
}


void Timer::start(const unsigned long timeToTimeout)
{
    m_timeToTimeout = timeToTimeout;
    m_timerIsRunning = true;
    setLastTimeoutToNow();    
}

void Timer::stop() 
{
    m_timerIsRunning = false;
}

bool Timer::isRunning() const
{
    return m_timerIsRunning;
}

void Timer::update() 
{
    if(m_timerIsRunning)
    {
        if(isATimeout())
        {
            doTimeout();
        }        
    }
}



void Timer::doTimeout() 
{
    doCallback();
    setLastTimeoutToNow();
}

bool Timer::isATimeout() const
{
    if(m_getTime == nullptr) return true;
    if(m_timeToTimeout == 0) return true;
    return ( m_getTime() - m_lastTimeout > m_timeToTimeout );
}


void Timer::setLastTimeoutToNow()
{
    if(m_getTime != nullptr)
    {
        m_lastTimeout = m_getTime();
    }
    else
    {
        m_lastTimeout = 0;
    }
}


} //namespace smpmcr

