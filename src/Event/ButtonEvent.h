#ifndef BUTTONEVENT_H
#define BUTTONEVENT_H

#include "Event.h"

namespace smpmcr
{
    class ButtonEvent : protected Event
    {
    public:

        ButtonEvent(unsigned long (*getTime)(), int (*readButton)(), const int buttonPressedState, const int buttonUnpressedState,
                    void (*pressCallback)() = nullptr,void (*doublePressCallback)() = nullptr, const unsigned long pressTime = 250, const unsigned long afterSinglePressWaitTime = 250);
        
        void setTimeFunction(unsigned long (*getTime)());
        void setReadButtonFunction(int (*readButton)());

        void setButtonPressedState(const int buttonPressedState);
        void setButtonUnpressedState(const int buttonUnpressedState);

        void setPressCallback(void (*pressCallback)());
        void setDoublePressCallback(void (*doublePressCallback)());
        
        void setPressTime(const unsigned long pressTime);
        void setAfterSinglePressWaitTime(const unsigned long afterSinglePressWaitTime);

        void update();

    private:
        unsigned long (*m_getTime)() = nullptr;
        int (*m_readButton)() = nullptr;
        void (*m_doublePressCallback)() = nullptr;

        int m_buttonPressedState;
        int m_buttonUnpressedState;
        unsigned long m_pressTime;
        unsigned long m_afterSinglePressWaitTime;

        void doDoublePressCallback();
        bool isPressEvent();
        bool isDoublePressEvent();
    };
}



#endif //BUTTONEVENT_H

