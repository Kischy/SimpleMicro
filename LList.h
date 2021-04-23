#ifndef LLIST_H
#define LLIST_H

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
    class Iterator;

    //Element acces
    virtual T& front() = 0;
    virtual const T& front() const = 0;

    //Iterators
    Iterator begin() = 0;
    Iterator end() = 0;

    //Capacity
    virtual bool empty() const;
    virtual size_t size() const;
    virtual size_t max_size() const = 0;

    //Modifiers
    virtual void clear() = 0;
    virtual void push_front(T&& value) = 0;
    virtual T pop_front() = 0;

    virtual void push_back(T&& value) = 0;
    virtual T pop_back() = 0; 
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