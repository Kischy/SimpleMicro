#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H

#include "../LList/StaticLList.h"
#include "Event.h"

namespace smpmcr
{

template<size_t MAX_NO_OF_EVENTS>
class EventListener
{
public:
bool add(Event* event)
{
    if(events.size() == maxSize()) return false;

    events.pushFront(event);
    return true;
}

bool remove(Event* event)
{
    size_t countRemoved = events.eraseAllFound(event,eventPtrCompare);
    return countRemoved > 0;
}

void updateAll()
{
    for(auto it = events.begin(); it != events.end(); ++it)
    {
        (*it)->update();
    }
}

size_t size() const {return events.size();}
static size_t maxSize() {return MAX_NO_OF_EVENTS;}

private:
StaticLList<Event*,MAX_NO_OF_EVENTS> events;

static bool eventPtrCompare( Event* const& lhs,  Event* const& rhs)
{
    return lhs == rhs;
}

};
}


#endif //EVENTLISTENER_H
