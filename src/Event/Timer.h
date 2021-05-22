#ifndef TIMER_H
#define TIMER_H

#include "Event.h"


namespace smpmcr
{

class Timer : public Event
{
public:
Timer(unsigned long (*getTime)(), void (*timeOutCallback)() = nullptr);

void start(unsigned long timeToTimeout);
void stop();

bool isRunning() const;
virtual void update() override;


private:
unsigned long (*m_getTime)() = nullptr;

void doTimeout();
bool isATimeout() const;
void setLastTimeoutToNow();

bool m_timerIsRunning = false;
unsigned long m_lastTimeout;
unsigned long m_timeToTimeout;


};



} //namespace smpmcr


#endif //TIMER_H