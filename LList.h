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
        value(value),nextElement(nextElement) {}

        T value;
        LListElement* nextElement = nullptr;
    };

    size_t elementCount = 0;
    LListElement* firstElement = nullptr;

public:
    class Iterator
    {
    private:
            LListElement *current = nullptr;

    public:
        Iterator(LListElement* startingElement)
        {
            current = startingElement;
        }

        T& operator*()  { return current->value;} 
        T* operator->() {return &current->value;}

        //Prefix increment
        Iterator& operator++() 
        {
            current = current->nextElement;
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
                if(it.current == nullptr) return it;
                it++;
            }
            return it;
        }

        friend bool operator==(const Iterator& lhs, const Iterator& rhs)
        {
            return lhs.current == rhs.current;
        }

        friend bool operator!=(const Iterator& lhs, const Iterator& rhs)
        {
            return lhs.current != rhs.current;
        }

                        
    };

    ~LList()
    {
        clear();
    }

    //Element access
    virtual T& front() { return firstElement->value;}
    virtual const T& front() const { return firstElement->value;}

    //Iterators
    Iterator begin() { return Iterator(firstElement); }
    Iterator end() { return Iterator(nullptr); }

    //Capacity
    virtual bool empty() const { return size() == 0;}
    virtual size_t size() const {return elementCount;}

    //Modifiers    
    void clear()
    {
        while(size() > 0)
        {
            pop_front();
        }
    }     

    virtual void push_front(const T& value) 
    {       
        LListElement* newFirstElement = new LListElement(value,firstElement);
        firstElement = newFirstElement;        

        elementCount++;
    }

    virtual void pop_front()
    {
        if(size() > 0)
        {
            LListElement* oldFirstElement = firstElement;
            firstElement = firstElement->nextElement;
            delete oldFirstElement;
            elementCount--;
        }

    }
    

};



}


#endif //LLIST_H