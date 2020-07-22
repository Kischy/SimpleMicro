#ifndef TIMER_H
#define TIMER_H

#include <functional>

namespace ck
{

class Timer
{
public:
Timer(std::function<unsigned long()> getTime);


private:
std::function<unsigned long()> getTime = nullptr;

};

}





#endif