#ifndef ILISTCOMMONTESTS_H
#define ILISTCOMMONTESTS_H

#include <gtest/gtest.h>
#include <memory>
#include "../LList/LListBase.h"

class LListBaseTests : public testing::TestWithParam< std::shared_ptr<smpmcr::LListBase<int>>>
{
    public:
    std::shared_ptr<smpmcr::LListBase<int>> testList = GetParam();
    

};


class LListBaseIteratorAndFrontTests : public testing::TestWithParam< std::shared_ptr<smpmcr::LListBase<int>>>
{
    public:
    std::shared_ptr<smpmcr::LListBase<int>> testList = GetParam();

    LListBaseIteratorAndFrontTests()
    {
        for(int i = 0; i < 10; ++i)
        {
            testList->push_front(i);
        }
    }
    

};

class IntHolder
{
public:
    IntHolder(int value)
    {
        this->holderValue = value;
    }

    int holderValue = 0;    
};


class LListBaseIteratorArrowOperatorTests : public testing::TestWithParam< std::shared_ptr<smpmcr::LListBase<IntHolder>>>
{
public:

    std::shared_ptr<smpmcr::LListBase<IntHolder>> testList = GetParam();

    LListBaseIteratorArrowOperatorTests()
    {
        for(int i = 0; i < 10; ++i)
        {
            testList->push_front(IntHolder(i));
        }
    }

};




#endif //ILISTCOMMONTESTS_H