#include <gtest/gtest.h>

#include <chrono>
#include <thread>


#include "Event/ButtonEvent.h"
#include "EventTestsHelper.h"

class ButtonEventTests : public testing::Test
{
public:
static const unsigned long buttonPressTime = 15;
static const unsigned long afterSinglePressTime = 30;

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

void doSinglePress()
{
    buttonMockCurrentState = buttonMockPressedState;
    buttonEv.update();
    std::this_thread::sleep_for(std::chrono::milliseconds(buttonPressTime+1));
    buttonEv.update();
    buttonMockCurrentState = buttonMockUnpressedState;
    buttonEv.update();

    std::this_thread::sleep_for(std::chrono::milliseconds(afterSinglePressTime+1));
    buttonEv.update();
}

void doDoublePress()
{
    buttonMockCurrentState = buttonMockPressedState;
    buttonEv.update();
    std::this_thread::sleep_for(std::chrono::milliseconds(buttonPressTime+1));
    buttonEv.update();
    buttonMockCurrentState = buttonMockUnpressedState;
    std::this_thread::sleep_for(std::chrono::milliseconds(afterSinglePressTime/4));
    buttonEv.update();

    buttonMockCurrentState = buttonMockPressedState;
    buttonEv.update();
    std::this_thread::sleep_for(std::chrono::milliseconds(buttonPressTime+1));
    buttonEv.update();
    buttonMockCurrentState = buttonMockUnpressedState;
    buttonEv.update();
}

void doSinglePressButPressAgainToFast()
{
    buttonMockCurrentState = buttonMockPressedState;
    buttonEv.update();
    std::this_thread::sleep_for(std::chrono::milliseconds(buttonPressTime+1));
    buttonEv.update();
    buttonMockCurrentState = buttonMockUnpressedState;
    buttonEv.update();

    //std::this_thread::sleep_for(std::chrono::milliseconds(afterSinglePressTime+1));
    buttonMockCurrentState = buttonMockPressedState;
    buttonEv.update();
}


void doSinglePressButDontPressLongEnough()
{
    buttonMockCurrentState = buttonMockPressedState;
    buttonEv.update();
    std::this_thread::sleep_for(std::chrono::milliseconds(buttonPressTime+1));
    buttonEv.update();
    buttonMockCurrentState = buttonMockUnpressedState;
    buttonEv.update();

   // std::this_thread::sleep_for(std::chrono::milliseconds(afterSinglePressTime+1));
   // buttonEv.update();
}


void doDoublePressButFirstPressIsToShort_whichResultsInASinglePressAtTheEnd()
{
    buttonMockCurrentState = buttonMockPressedState;
    buttonEv.update();
    //std::this_thread::sleep_for(std::chrono::milliseconds(buttonPressTime+1));
   // buttonEv.update();
    buttonMockCurrentState = buttonMockUnpressedState;
    std::this_thread::sleep_for(std::chrono::milliseconds(afterSinglePressTime/2));
    buttonEv.update();

    buttonMockCurrentState = buttonMockPressedState;
    buttonEv.update();
    std::this_thread::sleep_for(std::chrono::milliseconds(buttonPressTime+1));
    buttonEv.update();
    buttonMockCurrentState = buttonMockUnpressedState;
    buttonEv.update();
}

void doDoublePressButSecondPressIsToShort()
{
    buttonMockCurrentState = buttonMockPressedState;
    buttonEv.update();
    std::this_thread::sleep_for(std::chrono::milliseconds(buttonPressTime+1));
    buttonEv.update();
    buttonMockCurrentState = buttonMockUnpressedState;
    std::this_thread::sleep_for(std::chrono::milliseconds(afterSinglePressTime/4));
    buttonEv.update();

    buttonMockCurrentState = buttonMockPressedState;
    buttonEv.update();
    //std::this_thread::sleep_for(std::chrono::milliseconds(buttonPressTime+1));
   // buttonEv.update();
    buttonMockCurrentState = buttonMockUnpressedState;
    buttonEv.update();
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
    doSinglePress();
    ASSERT_TRUE(pressCallbackCalled);
    ASSERT_FALSE(doublePressCallbackCalled);
}

TEST_F(ButtonEventTests, ButtonPressedIsNotTriggeredOnlyIfAfterSinglePressTimeIsNotExceeded)
{
    doSinglePressButPressAgainToFast();
    ASSERT_FALSE(pressCallbackCalled);
    ASSERT_FALSE(doublePressCallbackCalled);
}

TEST_F(ButtonEventTests, ButtonPressedIsNotTriggeredOnlyIfSinglePressTimeIsNotExceeded)
{
    doSinglePressButDontPressLongEnough();
    ASSERT_FALSE(pressCallbackCalled);
    ASSERT_FALSE(doublePressCallbackCalled);
}



TEST_F(ButtonEventTests, ButtonDoublePressedIsTriggeredOnlyIfButtonIsPressedTwiceForButtonPressTimeAndTheTimeInBetweenIsLowerThanAfterSinglePressTime)
{
    doDoublePress();
    ASSERT_FALSE(pressCallbackCalled);
    ASSERT_TRUE(doublePressCallbackCalled);
}



TEST_F(ButtonEventTests, ButtonDoublePressedIsNotTriggeredIfOneOfThePressesIsToShort)
{
    doDoublePressButFirstPressIsToShort_whichResultsInASinglePressAtTheEnd();
    ASSERT_FALSE(pressCallbackCalled);
    ASSERT_FALSE(doublePressCallbackCalled);

    std::this_thread::sleep_for(std::chrono::milliseconds(afterSinglePressTime+1));
    buttonEv.update();
    ASSERT_TRUE(pressCallbackCalled);

    doDoublePressButSecondPressIsToShort();   
    ASSERT_TRUE(pressCallbackCalled);
    ASSERT_FALSE(doublePressCallbackCalled);
}





