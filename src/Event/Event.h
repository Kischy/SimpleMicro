#ifndef EVENT_H
#define EVENT_H

namespace smpmcr
{

class Event
{
    public:
        Event(void (*eventCallback)() = nullptr)    
        {
            setEventCallback(eventCallback);
        }

        void setEventCallback(void (*eventCallback)())
        {
            this->m_eventCallback = eventCallback;
        }
        virtual void update() = 0;

    protected:
        void doCallback()
        {
            if(m_eventCallback != nullptr)
            {
                m_eventCallback();
            }
        }
        
    private: 
        void (*m_eventCallback)() = nullptr;



};

}

#endif //EVENT_H
