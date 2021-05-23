#include <gtest/gtest.h>

#include <chrono>
#include <thread>

#include "Event/ButtonEvent.h"
#include "EventTestsHelper.h"



class ButtonEventTests : public testing::Test
{
public:
static const unsigned long buttonPressTime = 30;
static const unsigned long afterSinglePressTime = 50;

static const int buttonMockPressedState = 1;
static const int buttonMockUnpressedState = 0;
static int buttonMockCurrentState;
static bool pressCallbackCalled;
static bool doublePressCallbackCalled;

static int readButtonMockFunction()
{
   return buttonMockCurrentState;
}

static void pressCallback()
{
    pressCallbackCalled = true;
}


static void doublePressCallback()
{
    doublePressCallbackCalled = true;
}


smpmcr::ButtonEvent buttonEv = smpmcr::ButtonEvent(&test_helper::timeMilliSeconds,&readButtonMockFunction,buttonMockPressedState,buttonMockUnpressedState,
                                                    &pressCallback,&doublePressCallback,buttonPressTime,afterSinglePressTime);

ButtonEventTests()
{
    buttonMockCurrentState = -1;
    pressCallbackCalled = false;
    doublePressCallbackCalled = false;
}

};


int ButtonEventTests::buttonMockCurrentState = -1;
bool ButtonEventTests::pressCallbackCalled = false;
bool ButtonEventTests::doublePressCallbackCalled = false;


TEST_F(ButtonEventTests, NothingHappensIfNothingHappens)
{
    buttonEv.update();
    ASSERT_FALSE(pressCallbackCalled);
    ASSERT_FALSE(doublePressCallbackCalled);
}

TEST_F(ButtonEventTests, ButtonPressedIsTriggeredOnlyIfHighForButtonPressTimeAndLowAfterwardsForAfterSinglePressTime)
{
    buttonMockCurrentState = buttonMockPressedState;
    buttonEv.update();
    std::this_thread::sleep_for(std::chrono::milliseconds(buttonPressTime+1));
    buttonEv.update();
    buttonMockCurrentState = buttonMockUnpressedState;
    buttonEv.update();

    ASSERT_FALSE(pressCallbackCalled);
    ASSERT_FALSE(doublePressCallbackCalled);

    std::this_thread::sleep_for(std::chrono::milliseconds(afterSinglePressTime+1));
    buttonEv.update();
    ASSERT_TRUE(pressCallbackCalled);
    ASSERT_FALSE(doublePressCallbackCalled);
}

TEST_F(ButtonEventTests, ButtonDoublePressedIsTriggeredOnlyIfButtonIsPressedTwiceForButtonPressTimeAndTheTimeInBetweenIsLowerThanAfterSinglePressTime)
{
    buttonMockCurrentState = buttonMockPressedState;
    buttonEv.update();
    std::this_thread::sleep_for(std::chrono::milliseconds(buttonPressTime+1));
    buttonEv.update();
    buttonMockCurrentState = buttonMockUnpressedState;
    std::this_thread::sleep_for(std::chrono::milliseconds(afterSinglePressTime/2));
    buttonEv.update();
    ASSERT_FALSE(pressCallbackCalled);
    ASSERT_FALSE(doublePressCallbackCalled);

    buttonMockCurrentState = buttonMockPressedState;
    buttonEv.update();
    std::this_thread::sleep_for(std::chrono::milliseconds(buttonPressTime+1));
    buttonEv.update();
    buttonMockCurrentState = buttonMockUnpressedState;
    buttonEv.update();

    ASSERT_FALSE(pressCallbackCalled);
    ASSERT_TRUE(doublePressCallbackCalled);
}


