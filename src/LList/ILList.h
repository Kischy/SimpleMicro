#ifndef ILLIST_H
#define ILLIST_H


namespace smpmcr
{

template<class T>
class ILList
{

public:
    virtual ~ILList() {}

    //Element access
    virtual T& front() = 0;
    virtual const T& front() const = 0;

    //Capacity
    virtual bool empty() const = 0;
    virtual size_t size() const = 0;

    //Modifiers    
    virtual void clear() = 0;
    virtual void pushFront(const T& value) = 0;
    virtual void popFront() = 0;
    virtual bool eraseFirstFound(const T& value,bool (*isEqualComparisonFunc)(const T&, const T&))  = 0;
    virtual size_t eraseAllFound(const T& value,bool (*isEqualComparisonFunc)(const T&, const T&)) = 0;
};

}//namespace smpmcr


#endif //ILLIST_H

