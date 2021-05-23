#ifndef BUTTONEVENT_H
#define BUTTONEVENT_H


#ifdef SIMPLE_MICRO_FOR_ARDUINO
#include "Arduino.h"
#endif


#include "Event.h"

namespace smpmcr
{
    class ButtonEvent : public Event
    {
    public:

        #ifdef SIMPLE_MICRO_FOR_ARDUINO
        ButtonEvent(void (*pressCallback)() = nullptr,void (*doublePressCallback)() = nullptr, unsigned long (*getTime)() = &millis)
        : ButtonEvent(getTime,nullptr,HIGH,LOW,pressCallback,doublePressCallback)
        {        
        }
        #endif

        ButtonEvent(unsigned long (*getTime)(), int (*readButton)(int), const int buttonPressedState, const int buttonUnpressedState,
                    void (*pressCallback)() = nullptr,void (*doublePressCallback)() = nullptr, const unsigned long pressTime = 250, const unsigned long afterSinglePressWaitTime = 250);


        void setPin(const int pin)
        {
            m_pin = pin;

            #ifdef SIMPLE_MICRO_FOR_ARDUINO
            pinMode(m_pin, INPUT);
            m_readButton = &digitalRead;
            #endif
        }

        
        void setTimeFunction(unsigned long (*getTime)());
        void setReadButtonFunction(int (*readButton)(int));

        void setButtonPressedState(const int buttonPressedState);
        void setButtonUnpressedState(const int buttonUnpressedState);

        void setPressCallback(void (*pressCallback)());
        void setDoublePressCallback(void (*doublePressCallback)());
        
        void setPressTime(const unsigned long pressTime);
        void setAfterSinglePressWaitTime(const unsigned long afterSinglePressWaitTime);

        void update();

    private:
        unsigned long (*m_getTime)() = nullptr;
        int (*m_readButton)(int) = nullptr;
        void (*m_doublePressCallback)() = nullptr;

        int m_buttonPressedState;
        int m_buttonUnpressedState;
        unsigned long m_pressTime;
        unsigned long m_afterSinglePressWaitTime;


        void updatePressState();
        void doDoublePressCallback();

        bool buttonIsPressed();
        bool buttonIsUnpressed();
        unsigned long getTime();

        bool pressTimeWasSurpassed();
        bool afterSinglePressTimeWasSurpassed();
        bool timeWasSurpassed(const unsigned long startingTime, const unsigned long timeToSurpass);
        

        int m_pin = -1;
        unsigned long m_pressedTime = 0;
        unsigned long m_unpressedTime = 0;

        enum button_press_state
        {
           unpressed,
           possibly_pressed_for_first_time,
           is_pressed_first_time_exceeding_pressing_time, 
           was_pressed_once_and_is_now_unpressed, 
           was_single_pressed,
           possibliy_pressed_for_second_time,
           is_pressed_second_time_exceeding_pressing_time,
           was_double_pressed
        };

        button_press_state m_buttonState = button_press_state::unpressed;
    };
}



#endif //BUTTONEVENT_H

