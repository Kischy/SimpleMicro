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
            updatePressState();
            if(m_buttonState == button_press_state::was_single_pressed)
            {
                doCallback();
                m_buttonState = button_press_state::unpressed;
            }
            else if(m_buttonState == button_press_state::was_double_pressed)
            {
                doDoublePressCallback();
                m_buttonState = button_press_state::unpressed;
            }
        }

        void ButtonEvent::updatePressState()
        {
            if(buttonIsPressed())
            {
                if(m_buttonState == button_press_state::unpressed)
                {
                    m_buttonState = button_press_state::possibly_pressed_for_first_time;
                    m_pressedTime = getTime();
                }

                if( m_buttonState == button_press_state::possibly_pressed_for_first_time && pressTimeWasSurpassed())
                {
                    m_buttonState = button_press_state::is_pressed_first_time_exceeding_pressing_time;
                }

                if(m_buttonState == button_press_state::was_pressed_once_and_is_now_unpressed && afterSinglePressTimeWasSurpassed() == false)
                {
                    m_buttonState = button_press_state::possibliy_pressed_for_second_time;
                    m_pressedTime = getTime();
                }

                if(m_buttonState == button_press_state::possibliy_pressed_for_second_time && pressTimeWasSurpassed())
                {
                    m_buttonState = button_press_state::is_pressed_second_time_exceeding_pressing_time;
                }
            }
            else if(buttonIsUnpressed())
            {
                if(m_buttonState == button_press_state::is_pressed_first_time_exceeding_pressing_time)
                {
                    m_buttonState = button_press_state::was_pressed_once_and_is_now_unpressed;
                    m_unpressedTime = getTime();
                }

                if(m_buttonState == button_press_state::was_pressed_once_and_is_now_unpressed && afterSinglePressTimeWasSurpassed())
                {
                    m_buttonState = button_press_state::was_single_pressed;
                }                                

                if(m_buttonState == button_press_state::is_pressed_second_time_exceeding_pressing_time)
                {
                    m_buttonState = button_press_state::was_double_pressed;
                }

                // The button is upressed, but the pressing time was not exceeded
                if(m_buttonState == button_press_state::possibly_pressed_for_first_time || m_buttonState == button_press_state::possibliy_pressed_for_second_time)
                {
                    m_buttonState = button_press_state::unpressed;
                }


            }        
        }

        void ButtonEvent::doDoublePressCallback()
        {
            if(m_doublePressCallback != nullptr)
            {
                m_doublePressCallback();
            }
        }



        bool ButtonEvent::buttonIsPressed()
        {
            if(m_readButton == nullptr) return false;
            return m_readButton() == m_buttonPressedState;
        }

        bool ButtonEvent::buttonIsUnpressed()
        {
            if(m_readButton == nullptr) return false;
            return m_readButton() == m_buttonUnpressedState; 
        }

        unsigned long ButtonEvent::getTime()
        {
            if(m_getTime == nullptr) return 0;
            return m_getTime(); 
        }

        bool ButtonEvent::pressTimeWasSurpassed()
        {
            return timeWasSurpassed(m_pressedTime,m_pressTime);
        }

        bool ButtonEvent::afterSinglePressTimeWasSurpassed()
        {
            return timeWasSurpassed(m_unpressedTime,m_afterSinglePressWaitTime);
        }

        bool ButtonEvent::timeWasSurpassed(const unsigned long startingTime, const unsigned long timeToSurpass)
        {
            if(timeToSurpass == 0) return true;

            unsigned long time = getTime();
            if(time == 0) return false;

            return ( time - startingTime > timeToSurpass );
        }
}