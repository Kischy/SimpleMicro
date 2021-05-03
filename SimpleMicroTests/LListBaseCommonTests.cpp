#include "LListBaseCommonTests.h"


TEST_P(LListBaseTests, InitialSizeIsZero)
{
    ASSERT_EQ(testList->size(),0);
    ASSERT_TRUE(testList->empty());
}

TEST_P(LListBaseTests, SizeIncreasesOnPushing)
{
    testList->push_front(1);
    ASSERT_EQ(testList->size(),1);
    ASSERT_FALSE(testList->empty());

    testList->push_front(1);
    testList->push_front(1);
    ASSERT_EQ(testList->size(),3);
    ASSERT_FALSE(testList->empty());
}


TEST_P(LListBaseTests, IsEmptyAfterClear)
{
    testList->push_front(1);
    testList->push_front(1);
    testList->push_front(1);
    ASSERT_EQ(testList->size(),3);
    testList->clear();
    ASSERT_EQ(testList->size(),0);
    ASSERT_TRUE(testList->empty());
    ASSERT_TRUE(testList->begin() == testList->end());
}

TEST_P(LListBaseTests, SizeDecreasesOnPoping)
{
    testList->push_front(1);
    testList->push_front(1);
    testList->push_front(1);
    ASSERT_EQ(testList->size(),3);

    testList->pop_front();
    ASSERT_EQ(testList->size(),2);
    testList->pop_front();
    ASSERT_EQ(testList->size(),1);
    testList->pop_front();
    ASSERT_EQ(testList->size(),0);
    testList->pop_front();
    ASSERT_EQ(testList->size(),0);
}





TEST_P(LListBaseIteratorAndFrontTests, FrontReturnsFirstElement)
{
    ASSERT_EQ(testList->front(),9);
    testList->pop_front();
    ASSERT_EQ(testList->front(),8);
    testList->pop_front();
    ASSERT_EQ(testList->front(),7);
}


TEST_P(LListBaseIteratorAndFrontTests, BeginReturnsIteratorToFirstElement)
{
    smpmcr::LListBase<int>::Iterator it = testList->begin();
    ASSERT_EQ(*it,9);
}

TEST_P(LListBaseIteratorAndFrontTests, IteratorCanBeChanged)
{
    smpmcr::LListBase<int>::Iterator it = testList->begin();
    ASSERT_EQ(*it,9);

    *it = 200;
    ASSERT_EQ(*it,200);
    it = testList->begin();
    ASSERT_EQ(*it,200);
}

TEST_P(LListBaseIteratorAndFrontTests, BeginIteratorIsUnequalToEnd)
{
    ASSERT_FALSE(testList->begin() == testList->end());
    ASSERT_TRUE(testList->begin() != testList->end());
}

TEST_P(LListBaseIteratorAndFrontTests, IteratorCanBeIncremented)
{
    smpmcr::LListBase<int>::Iterator it = testList->begin();
    ASSERT_EQ(*it,9);
    ++it;
    ASSERT_EQ(*it,8);
    it++;
    ASSERT_EQ(*it,7);
    it += 3;
    ASSERT_EQ(*it,4);
    it = it + 3;
    ASSERT_EQ(*it,1);
}


TEST_P(LListBaseIteratorAndFrontTests, IteratorWorksInLoop)
{
    int i = 9;
    for(auto it = testList->begin(); it != testList->end(); ++it)
    {
        ASSERT_EQ(*it,i);
        i--;
    }

    i = 9;
    for(auto it = testList->begin(); it != testList->end(); it++)
    {
        ASSERT_EQ(*it,i);
        i--;
    }
}


TEST_P(LListBaseIteratorAndFrontTests, IteratorWorksInLoopWithDoubleAddition)
{
    int i = 9;
    for(auto it = testList->begin(); it != testList->end(); it = it + 2)
    {
        ASSERT_EQ(*it,i);
        i-=2;
    }

    i = 9;
    for(auto it = testList->begin(); it != testList->end(); it+=2)
    {
        ASSERT_EQ(*it,i);
        i-=2;
    }
}


TEST_P(LListBaseIteratorArrowOperatorTests, ArrowOperatorCanBeUsed)
{
    smpmcr::LListBase<IntHolder>::Iterator it = testList->begin();
    ASSERT_EQ(it->holderValue,9);
    *it = 200;
    ASSERT_EQ(it->holderValue,200);
    it = testList->begin();
    ASSERT_EQ(it->holderValue,200);
}

TEST_P(LListBaseIteratorArrowOperatorTests, IteratorWorksInLoopArrowOperator)
{
    int i = 9;
    for(auto it = testList->begin(); it != testList->end(); ++it)
    {
        ASSERT_EQ(it->holderValue,i);
        i--;
    }

    i = 9;
    for(auto it = testList->begin(); it != testList->end(); it++)
    {
        ASSERT_EQ(it->holderValue,i);
        i--;
    }
}





