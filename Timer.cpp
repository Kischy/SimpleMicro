#include "Timer.h"


namespace ck
{
    Timer::Timer(unsigned long (*getTime)())
    {
        this->getTime = getTime;
    }


}


