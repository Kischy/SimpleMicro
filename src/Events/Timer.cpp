#include "Timer.h"

namespace smpmcr
{

Timer::Timer(unsigned long (*getTime)(), void (*timeOutCallback)()) : Event(timeOutCallback)
{
    this->m_getTime = getTime;
}


void Timer::start(unsigned long timeToTimeout)
{
    this->m_timeToTimeout = timeToTimeout;
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
        if(m_getTime == nullptr)
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
    doCallback();
    setLastTimeoutToNow();
}

bool Timer::isATimeout() const
{
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

