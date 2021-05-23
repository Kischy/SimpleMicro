#ifndef LLISTBASE_H
#define LLISTBASE_H


#include "ILList.h"

//#include <stddef.h>


namespace smpmcr
{


template<class T>
class LListBase : public ILList<T>
{
    protected:
        class LListElement
        {
            public:
                LListElement() {}

                LListElement(const T& value, LListElement* nextElement) :
                m_value(value),m_nextElement(nextElement) {}

                T m_value;
                LListElement* m_nextElement = nullptr;
        };

        size_t m_elementCount = 0;
        LListElement* m_firstElement = nullptr;   

        bool isFirstElement(const LListElement* element) const
        {
            if(this->size() == 0) return false;
            return element == this->m_firstElement;
        }

        virtual void deleteElement(LListElement* oldFirstElement) = 0;
        virtual void removeElement(LListElement* element, LListElement* previousElement) = 0;

    public:
        class Iterator
        {
            private:
                    LListElement *m_current = nullptr;

            public:
                Iterator(LListElement* startingElement)
                {
                    m_current = startingElement;
                }

                T& operator*()  { return m_current->m_value;} 
                T* operator->() {return &m_current->m_value;}

                //Prefix increment
                Iterator& operator++() 
                {
                    m_current = m_current->m_nextElement;
                    return *this;
                }    

                //Postfix increment
                Iterator operator++(int)
                {
                    Iterator tmp = *this;  
                    ++(*this);
                    return tmp;
                }
                
                friend Iterator operator+=(Iterator& it, const size_t increment)
                {
                    return it + increment;
                }

                friend Iterator operator+(Iterator& it, const size_t increment)
                {
                    for(size_t i = 0; i < increment; ++i)
                    {
                        if(it.m_current == nullptr) return it;
                        it++;
                    }
                    return it;
                }

                friend bool operator==(const Iterator& lhs, const Iterator& rhs)
                {
                    return lhs.m_current == rhs.m_current;
                }

                friend bool operator!=(const Iterator& lhs, const Iterator& rhs)
                {
                    return lhs.m_current != rhs.m_current;
                }                        
        };

        virtual ~LListBase() {} 

        //Capacity
        virtual bool empty() const { return size() == 0;}
        virtual size_t size() const {return m_elementCount;}

        //Element access
        virtual T& front() { return m_firstElement->m_value;}
        virtual const T& front() const  { return m_firstElement->m_value;}

        //Iterators
        virtual Iterator begin() { return Iterator(m_firstElement); }
        virtual Iterator end() { return Iterator(nullptr); }

        //Modifiers    
        virtual void clear(); 
        virtual void pushFront(const T& m_value) = 0;
        virtual void popFront();
        virtual bool eraseFirstFound(const T& value,bool (*isEqualComparisonFunc)(const T&, const T&)) override;
        virtual size_t eraseAllFound(const T& value,bool (*isEqualComparisonFunc)(const T&, const T&)) override;

    };

template<class T>
void LListBase<T>::clear()
{
    while(size() > 0)
    {
        this->popFront();
    }
}   

template<class T>
void LListBase<T>::popFront()
{
    if(this->size() > 0)
    {
        LListElement* oldFirstElement = this->m_firstElement;
        this->m_firstElement = this->m_firstElement->m_nextElement;
        this->m_elementCount--;

        this->deleteElement(oldFirstElement);
    }
}   

template<class T>
bool LListBase<T>::eraseFirstFound(const T& value,bool (*isEqualComparisonFunc)(const T&, const T&))
{
    if(isEqualComparisonFunc == nullptr) return false;

    LListElement* previous = nullptr;
    LListElement* current = this->m_firstElement;

    for(size_t i = 0; i < this->size(); ++i)
    {
        if(isEqualComparisonFunc(current->m_value,value) == true)
        {
            this->removeElement(current,previous);
            return true;
        }

        previous = current;
        current = current->m_nextElement;
    }

    return false;
} 



template<class T>
size_t LListBase<T>::eraseAllFound(const T& value,bool (*isEqualComparisonFunc)(const T&, const T&))
{
    if(isEqualComparisonFunc == nullptr) return 0;
    size_t counter = 0;

    LListElement* previous = nullptr;
    LListElement* current = this->m_firstElement;

    for(size_t i = 0; i < this->size(); )
    {
        if(isEqualComparisonFunc(current->m_value,value) == true)
        {
            LListElement* nextCurrent = current->m_nextElement;

            this->removeElement(current,previous);
            counter++;
            current = nextCurrent;
        }
        else
        {
            previous = current;
            current = current->m_nextElement;
            ++i;
        }
    }

    return counter;
} 






} //namespace smpmcr


#endif //LLISTBASE_H

