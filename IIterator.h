#ifndef IITERATOR_H
#define IITERATOR_H


// TODO: Add tests

namespace smpmcr
{

template<class T>
class Iterator 
{

public:
    Iterator(T* valuePtr) = 0;
    T& operator*() = 0;
    Iterator& operator++() = 0;
    Iterator operator++(int) = 0;

};

}


#endif //IITERATOR_H