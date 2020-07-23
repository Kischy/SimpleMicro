#ifndef TIMER_H
#define TIMER_H



namespace ck
{
template
class ArdTimer
{
public:
ArdTimer(unsigned long (*getTime)())
{
    this->getTime = getTime;
}



private:
unsigned long (*getTime)();

};

}





#endif