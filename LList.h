#ifndef LLIST_H
#define LLIST_H

#include "IList.h"

namespace smpmcr
{


template<class T>
class LList
{
private:
    struct LListElement
    {
        T value;
        LListElement* nextElement = nullptr;
    };

    size_t elementCount = 0;
    LListElement* firstElement = nullptr;

public:
    bool empty() const;
    size_t size() const;



};


template<class T>
bool LList<T>::empty() const
{
    return size == 0;
}

template<class T>
size_t LList<T>::size() const
{
    return elementCount;
}


}


#endif //LLIST_H