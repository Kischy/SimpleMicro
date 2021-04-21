#ifndef LLIST_H
#define LLIST_H


template<class value_type>
class LList
{
private:
    struct LListElement
    {
        value_type value;
        LListElement* nextElement = nullptr;
    };

    size_t elementCount = 0;
    LListElement* firstElement = nullptr;

public:
    bool empty() const;
    size_t size() const;



};


template<class value_type>
bool LList<value_type>::empty() const
{
    return size == 0;
}

template<class value_type>
size_t LList<value_type>::size() const
{
    return elementCount;
}





#endif //LLIST_H