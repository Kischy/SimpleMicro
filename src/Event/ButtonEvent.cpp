#include "ButtonEvent.h"


namespace smpmcr
{

        ButtonEvent::ButtonEvent(unsigned long (*getTime)(), int (*readButton)(), const int buttonPressedState, const int buttonUnpressedState,
                            void (*pressCallback)(),void (*doublePressCallback)(), const unsigned long pressTime, const unsigned long afterSinglePressWaitTime)
        {
            setTimeFunction(getTime);
            setReadButtonFunction(readButton);
            setButtonPressedState(buttonPressedState);
            setButtonUnpressedState(buttonUnpressedState);
            setPressCallback(pressCallback);
            setDoublePressCallback(doublePressCallback);
            setPressTime(pressTime);
            setAfterSinglePressWaitTime(afterSinglePressWaitTime);
        }

        void ButtonEvent::setTimeFunction(unsigned long (*getTime)())
        {
            m_getTime = getTime;
        }


        void ButtonEvent::setReadButtonFunction(int (*readButton)())
        {
            m_readButton = readButton;
        }

        
        void ButtonEvent::setButtonPressedState(const int buttonPressedState)
        {
            m_buttonPressedState = buttonPressedState;
        }


        void ButtonEvent::setButtonUnpressedState(const int buttonUnpressedState)
        {
            m_buttonUnpressedState = buttonUnpressedState;
        }



        void ButtonEvent::setPressCallback(void (*pressCallback)())
        {
            setEventCallback(pressCallback);
        }

        void ButtonEvent::setDoublePressCallback(void (*doublePressCallback)())
        {
            m_doublePressCallback = doublePressCallback;
        }


        void ButtonEvent::setPressTime(const unsigned long pressTime)
        {
           m_pressTime = pressTime;
        }

        void ButtonEvent::setAfterSinglePressWaitTime(const unsigned long afterSinglePressWaitTime)
        {
            m_afterSinglePressWaitTime = afterSinglePressWaitTime;
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