#ifndef LLIST_H
#define LLIST_H

#include "LListBase.h"

namespace smpmcr
{

template<class T>
class LList : public LListBase<T>
{
private:
using ListElement = typename LListBase<T>::LListElement;

public:    
    virtual ~LList() override { this->clear(); }

    //Modifiers   
    virtual void push_front(const T& value) override;
    virtual void pop_front() override;   
};

template<class T>
void LList<T>::push_front(const T& value)
{      
   ListElement* newFirstElement = new ListElement(value,this->m_firstElement);
   this->m_firstElement = newFirstElement;        
   this->m_elementCount++;
}


template<class T>
void LList<T>::pop_front()
{
    if(this->size() > 0)
    {
        ListElement* oldFirstElement = this->m_firstElement;
        this->m_firstElement = this->m_firstElement->m_nextElement;
        delete oldFirstElement;
        this->m_elementCount--;
    }
}



} //namespace smpmcr


#endif //LLIST_H