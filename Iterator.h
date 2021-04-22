#ifndef ITERATOR_H
#define ITERATOR_H


// TODO: Add tests

namespace smpmcr
{

template<class T>
class Iterator 
{
private:
    T* valuePtr;
public:
    Iterator(T* valuePtr)
    {
        this->valuePtr = valuePtr;
    }

    T& operator*()
    {
        return *valuePtr;
    }

    Iterator& operator++()
    {
        valuePtr++;
        return *this;
    }

    Iterator operator++(int)
    {
        Iterator old = *this;
        operator++();
        return old;
    }

};

}


#endif //ITERATOR_H