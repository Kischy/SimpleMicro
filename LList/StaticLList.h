#ifndef STATICLLIST_H
#define STATICLLIST_H

#include "LListBase.h"

namespace smpmcr
{

template<class T,size_t MAX_SIZE>
class StaticLList : public LListBase<T>
{
private:
using ListElement = typename LListBase<T>::LListElement;

ListElement listElements[MAX_SIZE];

public:    
    virtual ~StaticLList() override { this->clear(); }

    static size_t max_size() {return MAX_SIZE;}

    //Modifiers   
    virtual void push_front(const T& value) override;
    virtual void pop_front() override;   
};

template<class T,size_t MAX_SIZE>
void StaticLList<T,MAX_SIZE>::push_front(const T& value)
{  
    const size_t curr_size = this->size();
    if(curr_size < MAX_SIZE)
    {
        ListElement* newFirstElement = &this->listElements[curr_size];
        newFirstElement->m_value = value;
        newFirstElement->m_nextElement = this->m_firstElement;
        this->m_firstElement = newFirstElement;        
        this->m_elementCount++;
    }
}


template<class T,size_t MAX_SIZE>
void StaticLList<T,MAX_SIZE>::pop_front()
{
    if(this->size() > 0)
    {
        this->m_firstElement = this->m_firstElement->m_nextElement;
        this->m_elementCount--;
    }
}



} //namespace smpmcr



#endif //STATICLLIST_H