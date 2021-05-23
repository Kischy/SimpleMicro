#ifndef BUTTONEVENT_H
#define BUTTONEVENT_H

#include "Event.h"

namespace smpmcr
{
    class ButtonEvent : protected Event
    {
        public:

        ButtonEvent(unsigned long (*getTime)(), int (*readButton)(), const int buttonHigh, const int buttonLow,
                    void (*pressCallback)() = nullptr,void (*doublePressCallback)() = nullptr, const unsigned long pressTime = 250, const unsigned long inBetweenPressesTime = 250);

        void setPressCallback(void (*pressCallback)());
        void setDoublePressCallback(void (*doublePressCallback)());

        void setButtonHigh(const int buttonHigh);
        void setButtonLow(const int buttonLow);

        void update();

        private:
        unsigned long (*m_getTime)() = nullptr;
        int (*m_readButton)() = nullptr;
        void (*m_doublePressCallback)() = nullptr;

        int m_buttonHigh;
        int m_buttonLow;
        unsigned long m_pressTime;
        unsigned long m_inBetweenPressesTime;

        void doDoublePressCallback();
        bool isPressEvent();
        bool isDoublePressEvent();
    };
}



#endif //BUTTONEVENT_H

