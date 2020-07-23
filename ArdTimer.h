#ifndef TIMER_H
#define TIMER_H



namespace ck
{
template<size_t maxNoOfObj>
class ArdTimer
{
public:
ArdTimer(unsigned long (*getTime)())
{
    this->getTime = getTime;
}

void start(unsigned long timeToTimeout)
{
    this->timeToTimeout = timeToTimeout;
    timerIsRunning = true;

    if(getTime != nullptr)
    {
        lastTimeout = getTime();
    }
    else
    {
        lastTimeout = 0;
    }
    
}

void stop()
{
    timerIsRunning = false;
}

bool isTimerRunning() const
{
    return timerIsRunning;
}

void checkForTimeout()
{
    if(timerIsRunning)
    {
        if(timeToTimeout == 0)
        {
            callTimeoutCallback();
        }
        else if(getTime == nullptr)
        {
            callTimeoutCallback();
        }
        else
        {
            if(isATimeout())
            {
                callTimeoutCallback();
            }             
        }
        
    }
}



private:
unsigned long (*getTime)() = nullptr;
void (*timeOutCallback)() = nullptr;


void callTimeoutCallback()
{
    if(timeOutCallback != nullptr)
    {
        timeOutCallback();
    }
}

bool isATimeout()
{
    return ( getTime() - lastTimeout > timeToTimeout );
}


bool timerIsRunning = false;
unsigned long lastTimeout;
unsigned long timeToTimeout;

};

}





#endif