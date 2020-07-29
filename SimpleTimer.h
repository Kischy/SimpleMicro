#ifndef SIMPLETIMER_H
#define SIMPLETIMER_H

namespace ck
{

class SimpleTimer
{
public:
SimpleTimer(unsigned long (*getTime)(), void (*timeOutCallback)() = nullptr);

void start(unsigned long timeToTimeout);
void stop();

bool isTimerRunning() const;
void checkForTimeout();



private:
unsigned long (*getTime)() = nullptr;
void (*timeOutCallback)() = nullptr;


void doTimeout();
bool isATimeout() const;
void setLastTimeoutToNow();

bool timerIsRunning = false;
unsigned long lastTimeout;
unsigned long timeToTimeout;


//Statics
//static *SimpleTimer[maxNoOfObj];

};



}


#endif //SIMPLETIMER_H