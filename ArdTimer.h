#ifndef TIMER_H
#define TIMER_H



namespace ck
{
template<size_t maxNoOfObj>
class ArdTimer
{
public:
ArdTimer(unsigned long (*getTime)(), void (*timeOutCallback)() = nullptr)
{
    this->getTime = getTime;
    this->timeOutCallback = timeOutCallback;
}

void start(unsigned long timeToTimeout)
{
    this->timeToTimeout = timeToTimeout;
    timerIsRunning = true;
    setLastTimeoutToNow();    
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



private:
unsigned long (*getTime)() = nullptr;
void (*timeOutCallback)() = nullptr;


void doTimeout() 
{
    if(timeOutCallback != nullptr)
    {
        timeOutCallback();
    }

    setLastTimeoutToNow();
}

bool isATimeout() const
{
    return ( getTime() - lastTimeout > timeToTimeout );
}

void setLastTimeoutToNow()
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


bool timerIsRunning = false;
unsigned long lastTimeout;
unsigned long timeToTimeout;


//Statics
//static *ArdTimer[maxNoOfObj];

};

}





#endif