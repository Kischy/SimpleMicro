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
unsigned long (*m_getTime)() = nullptr;
void (*m_timeOutCallback)() = nullptr;


void doTimeout();
bool isATimeout() const;
void setLastTimeoutToNow();

bool m_timerIsRunning = false;
unsigned long m_lastTimeout;
unsigned long m_timeToTimeout;


};



} //namespace smpmcr


#endif //TIMER_H