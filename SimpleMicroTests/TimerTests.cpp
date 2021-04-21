#include <gtest/gtest.h>

#include <chrono>
#include <thread>
#include <string>

#include "../Timer.h"

class TimerTests : public testing::Test
{
public:

    smpmcr::Timer timer = smpmcr::Timer(&TimerTests::timeMilliSeconds, &TimerTests::timeOutFunction);

    static bool wasCalled;

    static unsigned long timeMilliSeconds() 
    {
        auto now = std::chrono::system_clock::now();
        auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
        auto epoch = now_ms.time_since_epoch();
        auto value = std::chrono::duration_cast<std::chrono::milliseconds>(epoch);
        return static_cast<unsigned long>(value.count());
    }

    static void timeOutFunction()
    {
        wasCalled = true;
    }

    TimerTests()
    {
        wasCalled = false;
    }


};

bool TimerTests::wasCalled = false;



TEST_F(TimerTests, CallsEventHandlerAfterTimeOut)
{
    ASSERT_FALSE(TimerTests::wasCalled);
    unsigned long timeoutTimeMS = 60;
    timer.start(timeoutTimeMS);

    std::this_thread::sleep_for(std::chrono::milliseconds(timeoutTimeMS/3));
    timer.listen();
    ASSERT_FALSE(TimerTests::wasCalled);

    std::this_thread::sleep_for(std::chrono::milliseconds(timeoutTimeMS*2/3 + 1));
    timer.listen();
    ASSERT_TRUE(TimerTests::wasCalled);
}

TEST_F(TimerTests, CallingStopStopsTimerAndEventHandlerIsNeverCalled)
{
    ASSERT_FALSE(TimerTests::wasCalled);
    timer.start(0);
    ASSERT_TRUE(timer.isRunning());

    timer.stop();
    timer.listen();
    ASSERT_FALSE(timer.isRunning());
    ASSERT_FALSE(TimerTests::wasCalled);
}


TEST_F(TimerTests, TimeOutIsCalledIsWithinAcceptableRange)
{
    ASSERT_FALSE(TimerTests::wasCalled);
    unsigned long timeoutTime_ms = 30;
    timer.start(timeoutTime_ms);

    const unsigned long start = timeMilliSeconds();   

    while(TimerTests::wasCalled == false)
    {
        timer.listen();
    }

    const unsigned long meassuredTime_ms = timeMilliSeconds() - start; 
    const unsigned long acceptableDeviation_ms  = 2;

    std::stringstream errorMsg;
    errorMsg << "Timer timeout was not within acceptable range:\n";
    errorMsg << "timeout time: " << timeoutTime_ms << " ms\n"; 
    errorMsg << "meassured time: " << meassuredTime_ms << " ms\n"; 
    errorMsg << "acceptable deviation: " << acceptableDeviation_ms << " ms"; 

    ASSERT_TRUE(meassuredTime_ms + acceptableDeviation_ms >= timeoutTime_ms && 
            timeoutTime_ms >= meassuredTime_ms - acceptableDeviation_ms) << errorMsg.str();
}



TEST_F(TimerTests, TimesOutImmediatelyForZeroTimeout)
{
    timer.start(0);
    ASSERT_FALSE(TimerTests::wasCalled);
    timer.listen();
    ASSERT_TRUE(TimerTests::wasCalled);
}



TEST_F(TimerTests, DoesNotCallEventHandlerIfListenIsNotCalled)
{
    timer.start(0);
    ASSERT_FALSE(TimerTests::wasCalled);
}



TEST_F(TimerTests, IsRunningAfterStart)
{
    timer.start(0);
    ASSERT_TRUE(timer.isRunning());
}


TEST_F(TimerTests, TimeOutIsCalledImmediatelyWhenNoTimerFunctionIsPresent)
{
    ASSERT_FALSE(TimerTests::wasCalled);
    smpmcr::Timer timerNoTimeOutFct = smpmcr::Timer(nullptr, &TimerTests::timeOutFunction);
    timerNoTimeOutFct.start(10000000);
    timerNoTimeOutFct.listen(); 

    ASSERT_TRUE(TimerTests::wasCalled);
}

TEST_F(TimerTests, DoesNothingWithNoEventHandler)
{
    ASSERT_FALSE(TimerTests::wasCalled);
    smpmcr::Timer timerEventHandler = smpmcr::Timer(nullptr, nullptr);
    timerEventHandler.start(10000000);
    timerEventHandler.listen();  

    ASSERT_FALSE(TimerTests::wasCalled);
}



