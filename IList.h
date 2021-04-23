#ifndef ILIST_H
#define ILIST_H


namespace smpmcr
{
template<class T>
class IList 
{
public:
    virtual ~IList() {}

    //Element acces
    virtual T& front() = 0;
    virtual const T& front() const = 0;

    //Iterators
    Iterator<T> begin() = 0;
    Iterator<T> end() = 0;

    //Capacity
    virtual bool empty() const = 0;
    virtual size_t size() const = 0;
    virtual size_t max_size() const = 0;

    //Modifiers
    virtual void clear() = 0;
    virtual void push_front(T&& value) = 0;
    virtual T pop_front() = 0;

    virtual void push_back(T&& value) = 0;
    virtual T pop_back() = 0;   
    



};



}

#endif //ILIST_H