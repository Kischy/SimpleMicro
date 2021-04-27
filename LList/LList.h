#ifndef LLIST_H
#define LLIST_H

namespace smpmcr
{

template<class T>
class LList
{
private:
    class LListElement
    {
    public:
        LListElement(const T& value, LListElement* nextElement) :
        m_value(value),m_nextElement(nextElement) {}

        T m_value;
        LListElement* m_nextElement = nullptr;
    };

    size_t m_elementCount = 0;
    LListElement* m_firstElement = nullptr;

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

    ~LList() { clear(); }

    //Element access
    virtual T& front() { return m_firstElement->m_value;}
    virtual const T& front() const { return m_firstElement->m_value;}

    //Iterators
    Iterator begin() { return Iterator(m_firstElement); }
    Iterator end() { return Iterator(nullptr); }

    //Capacity
    virtual bool empty() const { return size() == 0;}
    virtual size_t size() const {return m_elementCount;}

    //Modifiers    
    void clear();  

    virtual void push_front(const T& m_value);
    virtual void pop_front();   

};

template<class T>
void LList<T>::clear()
{
    while(size() > 0)
    {
        pop_front();
    }
}   

template<class T>
void LList<T>::push_front(const T& m_value)
{       
    LListElement* newFirstElement = new LListElement(m_value,m_firstElement);
    m_firstElement = newFirstElement;        

    m_elementCount++;
}

template<class T>
void LList<T>::pop_front()
{
    if(size() > 0)
    {
        LListElement* oldFirstElement = m_firstElement;
        m_firstElement = m_firstElement->m_nextElement;
        delete oldFirstElement;
        m_elementCount--;
    }
}


} //namespace smpmcr


#endif //LLIST_H