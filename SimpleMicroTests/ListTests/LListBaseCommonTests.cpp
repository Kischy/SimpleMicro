#include "LListBaseCommonTests.h"


TEST_P(LListBaseTests, InitialSizeIsZero)
{
    ASSERT_EQ(testList->size(),0);
    ASSERT_TRUE(testList->empty());
}

TEST_P(LListBaseTests, SizeIncreasesOnPushing)
{
    testList->pushFront(1);
    ASSERT_EQ(testList->size(),1);
    ASSERT_FALSE(testList->empty());

    testList->pushFront(1);
    testList->pushFront(1);
    ASSERT_EQ(testList->size(),3);
    ASSERT_FALSE(testList->empty());
}


TEST_P(LListBaseTests, IsEmptyAfterClear)
{
    testList->pushFront(1);
    testList->pushFront(1);
    testList->pushFront(1);
    ASSERT_EQ(testList->size(),3);
    testList->clear();
    ASSERT_EQ(testList->size(),0);
    ASSERT_TRUE(testList->empty());
    ASSERT_TRUE(testList->begin() == testList->end());
}

TEST_P(LListBaseTests, SizeDecreasesOnPoping)
{
    testList->pushFront(1);
    testList->pushFront(1);
    testList->pushFront(1);
    ASSERT_EQ(testList->size(),3);

    testList->popFront();
    ASSERT_EQ(testList->size(),2);
    testList->popFront();
    ASSERT_EQ(testList->size(),1);
    testList->popFront();
    ASSERT_EQ(testList->size(),0);
    testList->popFront();
    ASSERT_EQ(testList->size(),0);
}


TEST_P(LListBaseTests, CanBePushedAndPopedMultipleTimes)
{
    testList->pushFront(1);

    for(int i = 0; i < 10; ++i)
    {
        testList->pushFront(2);
        ASSERT_EQ(testList->front(),2);
        ASSERT_EQ(testList->size(),2);

        testList->popFront();
        ASSERT_EQ(testList->front(),1);
        ASSERT_EQ(testList->size(),1);
    }

    testList->pushFront(2);
    testList->pushFront(3);
    ASSERT_EQ(testList->front(),3);
    ASSERT_EQ(testList->size(),3);

    testList->popFront();
    ASSERT_EQ(testList->front(),2);
    ASSERT_EQ(testList->size(),2);

    testList->popFront();
    ASSERT_EQ(testList->front(),1);
    ASSERT_EQ(testList->size(),1);

    testList->popFront();
    ASSERT_EQ(testList->size(),0);

}

TEST_P(LListBaseEraseTests, EraseAllFoundReturnsNumberOfErases)
{
    ASSERT_EQ(testList->eraseAllFound(1,comparisonFunc),4);
    ASSERT_EQ(testList->eraseAllFound(3,comparisonFunc),1);
    ASSERT_EQ(testList->eraseAllFound(6,comparisonFunc),0);
    testList->clear();
    ASSERT_EQ(testList->eraseAllFound(2,comparisonFunc),0);
}


TEST_P(LListBaseEraseTests, EraseWorksCorrectlyAndListCanStillBeUsed)
{
    ASSERT_EQ(testList->eraseAllFound(1,comparisonFunc),4);
    ASSERT_TRUE(testList->eraseFirstFound(5,comparisonFunc));

    smpmcr::LListBase<long>::Iterator it = testList->begin();

    ASSERT_EQ(*it,3);
    ASSERT_EQ(*(++it),2);

    testList->pushFront(6);
    testList->pushFront(7);
    testList->pushFront(8);

    it = testList->begin();
    ASSERT_EQ(*it,8);
    ASSERT_EQ(*(++it),7);
    ASSERT_EQ(*(++it),6);
    ASSERT_EQ(*(++it),3);
    ASSERT_EQ(*(++it),2);

    testList->pushFront(6);
    testList->pushFront(7);
    testList->pushFront(8);

    ASSERT_TRUE(testList->eraseFirstFound(3,comparisonFunc));
    ASSERT_EQ(testList->eraseAllFound(6,comparisonFunc),2);

    it = testList->begin();
    ASSERT_EQ(*it,8);
    ASSERT_EQ(*(++it),7);
    ASSERT_EQ(*(++it),8);
    ASSERT_EQ(*(++it),7);
    ASSERT_EQ(*(++it),2);

    ASSERT_EQ(testList->eraseAllFound(8,comparisonFunc),2);
    ASSERT_EQ(testList->eraseAllFound(7,comparisonFunc),2);
    ASSERT_EQ(testList->eraseAllFound(2,comparisonFunc),1);
    ASSERT_EQ(testList->size(),0);

}


TEST_P(LListBaseEraseTests, EraseFristReturnsFalseIfNothingIsReturnedAndTrueOtherwise)
{
    ASSERT_FALSE(testList->eraseFirstFound(6,comparisonFunc));
    ASSERT_TRUE(testList->eraseFirstFound(5,comparisonFunc));
    ASSERT_TRUE(testList->eraseFirstFound(3,comparisonFunc));
}

TEST_P(LListBaseEraseTests, EraseFirstErasesFirstElementFoundAndOrderStaysTheSame)
{
    ASSERT_TRUE(testList->eraseFirstFound(1,comparisonFunc));
    smpmcr::LListBase<long>::Iterator it = testList->begin();

    ASSERT_EQ(*it,5);
    ASSERT_EQ(*(++it),1);
    ASSERT_EQ(*(++it),3);
    ASSERT_EQ(*(++it),1);
    ASSERT_EQ(*(++it),2);
    ASSERT_EQ(*(++it),1);

    testList->pushFront(6);
    testList->pushFront(7);
    testList->pushFront(8);

    it = testList->begin();
    ASSERT_EQ(*it,8);
    ASSERT_EQ(*(++it),7);
    ASSERT_EQ(*(++it),6);
    ASSERT_EQ(*(++it),5);
    ASSERT_EQ(*(++it),1);
    ASSERT_EQ(*(++it),3);
    ASSERT_EQ(*(++it),1);
    ASSERT_EQ(*(++it),2);
    ASSERT_EQ(*(++it),1);

    ASSERT_TRUE(testList->eraseFirstFound(1,comparisonFunc));
    testList->pushFront(6);
    testList->pushFront(7);
    testList->pushFront(8);
    it = testList->begin();
    ASSERT_EQ(*it,8);
    ASSERT_EQ(*(++it),7);
    ASSERT_EQ(*(++it),6);
    ASSERT_EQ(*(++it),8);
    ASSERT_EQ(*(++it),7);
    ASSERT_EQ(*(++it),6);
    ASSERT_EQ(*(++it),5);
    ASSERT_EQ(*(++it),3);
    ASSERT_EQ(*(++it),1);
    ASSERT_EQ(*(++it),2);
    ASSERT_EQ(*(++it),1);
}




TEST_P(LListBaseIteratorAndFrontTests, FrontReturnsFirstElement)
{
    ASSERT_EQ(testList->front(),9);
    testList->popFront();
    ASSERT_EQ(testList->front(),8);
    testList->popFront();
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





