#ifndef TIMER_H
#define TIMER_H

namespace smpmcr
{

class Timer
{
public:
Timer(unsigned long (*getTime)(), void (*timeOutCallback)() = nullptr);

void start(unsigned long timeToTimeout);
void stop();

bool isRunning() const;
void update();



private:
unsigned long (*getTime)() = nullptr;
void (*timeOutCallback)() = nullptr;


void doTimeout();
bool isATimeout() const;
void setLastTimeoutToNow();

bool timerIsRunning = false;
unsigned long lastTimeout;
unsigned long timeToTimeout;


};



}


#endif //TIMER_H