#ifndef TIMER_H
#define TIMER_H

#include <future>

namespace ck
{

class Timer
{
public:
Timer(unsigned long (*getTime)());


private:
unsigned long (*getTime)();

};

}





#endif