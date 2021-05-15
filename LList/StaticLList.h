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
ListElement* m_lastElement = nullptr;   


bool isLastElement(const ListElement* element) const
{
    if(this->size() == 0) return false;
    return element == this->m_lastElement;
}

bool isFreeElement(const ListElement* element) const
{
    return element->m_nextElement == nullptr;
}

size_t getNextArrayPosition() const
{
    for(size_t i = 0; i < MAX_SIZE; ++i)
    {
        if(isFreeElement(&listElements[i]) && isLastElement(&listElements[i]) == false)
        {
            return i;
        }
    }

    return MAX_SIZE;    
}

virtual void deleteElement(ListElement* oldFirstElement) override
{
    oldFirstElement->m_nextElement = nullptr;       
    if(this->size() == 0) this->m_lastElement = nullptr;
}


void removeElement(ListElement* element, ListElement* previousElement) override
{
    if(this->isFirstElement(element) == true)
    {
        this->pop_front();
    }
    else
    {
        if(isLastElement(element))
        {
            m_lastElement = previousElement;
        }

        previousElement->m_nextElement = element->m_nextElement;
        this->m_elementCount--;
        deleteElement(element);
    }
}




public:    
    virtual ~StaticLList() override { this->clear(); }

    static size_t max_size() {return MAX_SIZE;}

    //Modifiers   
    virtual void push_front(const T& value) override;
};

template<class T,size_t MAX_SIZE>
void StaticLList<T,MAX_SIZE>::push_front(const T& value)
{  
    const size_t curr_size = this->size();
    if(curr_size < MAX_SIZE)
    {
        const size_t position = getNextArrayPosition();
        ListElement* newFirstElement = &this->listElements[position];

        newFirstElement->m_value = value;
        newFirstElement->m_nextElement = this->m_firstElement;
        this->m_firstElement = newFirstElement;      

        if(curr_size == 0) this->m_lastElement = this->m_firstElement;

        this->m_elementCount++;
    }
}


} //namespace smpmcr



#endif //STATICLLIST_H