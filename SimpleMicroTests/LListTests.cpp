#include <gtest/gtest.h>

#include "../LList.h"

#include <vector>



class LListTests : public testing::Test
{
public:
    smpmcr::LList<int> testList;

};


TEST_F(LListTests, InitialSizeIsZero)
{
    ASSERT_EQ(testList.size(),0);
    ASSERT_TRUE(testList.empty());
}

TEST_F(LListTests, SizeIncreasesOnPushing)
{
    testList.push_front(1);
    ASSERT_EQ(testList.size(),1);
    ASSERT_FALSE(testList.empty());

    testList.push_front(1);
    testList.push_front(1);
    ASSERT_EQ(testList.size(),3);
    ASSERT_FALSE(testList.empty());
}


TEST_F(LListTests, IsActuallyEmptyAfterClear)
{
    testList.push_front(1);
    testList.push_front(1);
    testList.push_front(1);
    ASSERT_EQ(testList.size(),3);
    testList.clear();
    ASSERT_EQ(testList.size(),0);
    ASSERT_TRUE(testList.empty());
    ASSERT_TRUE(testList.begin() == testList.end());
}

TEST_F(LListTests, SizeDecreasesOnPoping)
{
    testList.push_front(1);
    testList.push_front(1);
    testList.push_front(1);
    ASSERT_EQ(testList.size(),3);

    testList.pop_front();
    ASSERT_EQ(testList.size(),2);
    testList.pop_front();
    ASSERT_EQ(testList.size(),1);
    testList.pop_front();
    ASSERT_EQ(testList.size(),0);
    testList.pop_front();
    ASSERT_EQ(testList.size(),0);
}

class LListIteratorAndFrontTests : public testing::Test
{
public:
    smpmcr::LList<int> testList;

    LListIteratorAndFrontTests()
    {
        for(int i = 0; i < 10; ++i)
        {
            testList.push_front(i);
        }
    }

};

TEST_F(LListIteratorAndFrontTests, FrontReturnsFirstElement)
{
    ASSERT_EQ(testList.front(),9);
    testList.pop_front();
    ASSERT_EQ(testList.front(),8);
    testList.pop_front();
    ASSERT_EQ(testList.front(),7);
}


TEST_F(LListIteratorAndFrontTests, BeginReturnsIteratorToFirstElement)
{
    smpmcr::LList<int>::Iterator it = testList.begin();
    ASSERT_EQ(*it,9);
}

TEST_F(LListIteratorAndFrontTests, IteratorCanBeChanged)
{
    smpmcr::LList<int>::Iterator it = testList.begin();
    ASSERT_EQ(*it,9);

    *it = 200;
    ASSERT_EQ(*it,200);
    it = testList.begin();
    ASSERT_EQ(*it,200);
}

TEST_F(LListIteratorAndFrontTests, BeginIteratorIsUnequalToEnd)
{
    ASSERT_FALSE(testList.begin() == testList.end());
    ASSERT_TRUE(testList.begin() != testList.end());
}

TEST_F(LListIteratorAndFrontTests, IteratorCanBeIncremented)
{
    smpmcr::LList<int>::Iterator it = testList.begin();
    ASSERT_EQ(*it,9);
    ++it;
    ASSERT_EQ(*it,8);
    it++;
    ASSERT_EQ(*it,7);
}

TEST_F(LListIteratorAndFrontTests, IteratorWorksInLoop)
{
    int i = 9;
    for(auto it = testList.begin(); it != testList.end(); ++it)
    {
        ASSERT_EQ(*it,i);
        i--;
    }

    i = 9;
    for(auto it = testList.begin(); it != testList.end(); it++)
    {
        ASSERT_EQ(*it,i);
        i--;
    }
}


TEST_F(LListIteratorAndFrontTests, IteratorWorksInLoopDoubleAddition)
{
    int i = 9;
    for(auto it = testList.begin(); it != testList.end(); it = it + 2)
    {
        ASSERT_EQ(*it,i);
        i-=2;
    }

    i = 9;
    for(auto it = testList.begin(); it != testList.end(); it+=2)
    {
        ASSERT_EQ(*it,i);
        i-=2;
    }
}





class LListIteratorArrowOperatorTests : public testing::Test
{
public:
    class IntHolder
    {
    public:
        IntHolder(int value)
        {
            this->holderValue = value;
        }

        int holderValue = 0;    
    };


    smpmcr::LList<IntHolder> testList;

    LListIteratorArrowOperatorTests()
    {
        for(int i = 0; i < 10; ++i)
        {
            testList.push_front(IntHolder(i));
        }
    }

};

TEST_F(LListIteratorArrowOperatorTests, ArrowOperatorCanBeUsed)
{
    smpmcr::LList<IntHolder>::Iterator it = testList.begin();
    ASSERT_EQ(it->holderValue,9);

    *it = 200;
    ASSERT_EQ(it->holderValue,200);
    it = testList.begin();
    ASSERT_EQ(it->holderValue,200);
}

TEST_F(LListIteratorArrowOperatorTests, IteratorWorksInLoopArrowOperator)
{
    int i = 9;
    for(auto it = testList.begin(); it != testList.end(); ++it)
    {
        ASSERT_EQ(it->holderValue,i);
        i--;
    }

    i = 9;
    for(auto it = testList.begin(); it != testList.end(); it++)
    {
        ASSERT_EQ(it->holderValue,i);
        i--;
    }
}

