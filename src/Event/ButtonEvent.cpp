#include "ButtonEvent.h"


namespace smpmcr
{

        ButtonEvent::ButtonEvent(unsigned long (*getTime)(), int (*readButton)(), const int buttonHigh, const int buttonLow,
                            void (*pressCallback)(),void (*doublePressCallback)(), const unsigned long pressTime, const unsigned long inBetweenPressesTime)
        {
            m_getTime = getTime;
            m_readButton = readButton;
            m_buttonHigh = buttonHigh;
            m_buttonLow = buttonLow;
            setPressCallback(pressCallback);
            setDoublePressCallback(doublePressCallback);
            m_pressTime = pressTime;
            m_inBetweenPressesTime = inBetweenPressesTime;
        }

        void ButtonEvent::setPressCallback(void (*pressCallback)())
        {
            this->setEventCallback(pressCallback);
        }

        void ButtonEvent::setDoublePressCallback(void (*doublePressCallback)())
        {
            m_doublePressCallback = doublePressCallback;
        }

        void ButtonEvent::setButtonHigh(const int buttonHigh)
        {
            m_buttonHigh = buttonHigh;
        }


        void ButtonEvent::setButtonLow(const int buttonLow)
        {
            m_buttonLow = buttonLow;
        }

        void ButtonEvent::update()
        {
            if(isPressEvent())
            {
                doCallback();
            }
            else if(isDoublePressEvent())
            {
                doDoublePressCallback();
            }
        }

        void ButtonEvent::doDoublePressCallback()
        {
            if(m_doublePressCallback != nullptr)
            {
                m_doublePressCallback();
            }
        }

        bool ButtonEvent::isPressEvent()
        {
            return true;
        }
        
        bool ButtonEvent::isDoublePressEvent()
        {
            return true;
        }
}