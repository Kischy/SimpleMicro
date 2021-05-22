#include <gtest/gtest.h>

#include "Event/Event.h"
#include "Event/EventListener.h"



class TestEvent : public smpmcr::Event
{
    public:
    TestEvent(void (*eventCallback)() = nullptr) : Event(eventCallback)
    { }

    virtual void update() override
    {
        doCallback();
    }
};


class EventListenerTests : public testing::Test
{
public:
TestEvent event1 = TestEvent(&incrementCallbackCounter);
TestEvent event2 = TestEvent(&incrementCallbackCounter);
TestEvent event3 = TestEvent(&incrementCallbackCounter);

smpmcr::EventListener<4> eventListener;


EventListenerTests()
{
   eventListener.add(&event1);
   eventListener.add(&event2);
   eventListener.add(&event3);

   counter = 0;
}

static int counter;

private:
static void incrementCallbackCounter()
{
    counter++;
}


};

int EventListenerTests::counter = 0;

TEST_F(EventListenerTests, HasSize4AfterAdding4Events)
{
    ASSERT_EQ(eventListener.size(),3);
}

TEST_F(EventListenerTests, RemovingAnAlementReducedSize)
{
    ASSERT_TRUE(eventListener.remove(&event1));
    ASSERT_EQ(eventListener.size(),2);
}

TEST_F(EventListenerTests, RemoveRemovesAllElements)
{
    ASSERT_TRUE(eventListener.add(&event1));
    ASSERT_TRUE(eventListener.remove(&event1));
    ASSERT_EQ(eventListener.size(),2);
}


TEST_F(EventListenerTests, AddingElementsWorksUntilMaxSizeIsReached)
{
    ASSERT_TRUE(eventListener.add(&event1));
    ASSERT_EQ(eventListener.size(),4);
    ASSERT_FALSE(eventListener.add(&event1));
    ASSERT_EQ(eventListener.size(),4);
}

TEST_F(EventListenerTests, MaxSizeReturnsCorrectMaxSize)
{
    ASSERT_EQ(eventListener.maxSize(),4);
}


TEST_F(EventListenerTests, UpdateAllCallsAllEventsUpdateFunction)
{
    eventListener.updateAll();
    ASSERT_EQ(EventListenerTests::counter, 3);
}


TEST_F(EventListenerTests, UpdateCallsEventsThatAreTwiceInTheListTwice)
{
    ASSERT_TRUE(eventListener.add(&event1));
    eventListener.updateAll();
    ASSERT_EQ(EventListenerTests::counter, 4);
}

TEST_F(EventListenerTests, UpdateDoesNotCallRemovedEvents)
{
    ASSERT_TRUE(eventListener.add(&event1));
    eventListener.updateAll();
    ASSERT_EQ(EventListenerTests::counter, 4);
    ASSERT_TRUE(eventListener.remove(&event1));
    eventListener.updateAll();
    ASSERT_EQ(EventListenerTests::counter, 6);
}



