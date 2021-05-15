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

virtual void deleteOldFirstElement(ListElement* oldFirstElement) override
{
    delete oldFirstElement;
}


void removeElement(ListElement* element, ListElement* previousElement) override
{
    if(this->isFirstElement(element) == true)
    {
        this->pop_front();
    }
    else
    {
        previousElement->m_nextElement = element->m_nextElement;
        delete element;
        this->m_elementCount--;
    }
}


public:    
    virtual ~LList() override { this->clear(); }

    //Modifiers   
    virtual void push_front(const T& value) override;

};

template<class T>
void LList<T>::push_front(const T& value)
{      
   ListElement* newFirstElement = new ListElement(value,this->m_firstElement);
   this->m_firstElement = newFirstElement;        
   this->m_elementCount++;
}


} //namespace smpmcr


#endif //LLIST_H