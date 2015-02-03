
#pragma once

namespace Windows
{
    class CEvent
    {
        NO_COPY(CEvent);

    protected:
        explicit CEvent(bool manual);

        ~CEvent(void);

    public:
        operator HANDLE() const;

    public:
        void Wait();

        void Set();

    protected:
        const HANDLE m_hEvent;
    };

    class CAutoResetEvent : public CEvent
    {
    public:
        CAutoResetEvent(void);
    };

    class CManualResetEvent : public CEvent
    {
    public:
        CManualResetEvent(void);

    public:
        void Reset();

        bool IsSet() const;

        bool IsNotSet() const;
    };

    template <class T>
    struct ObjectWithEvent : public T
    {
        CAutoResetEvent Event;
    };

    template <class T>
    class CObjectWithEventPtr
    {
        NO_COPY(CObjectWithEventPtr);

    public:
        explicit CObjectWithEventPtr(ObjectWithEvent<T>& objectWithEvent)
            : m_objectWithEvent(objectWithEvent)
        {
        }

        ~CObjectWithEventPtr(void)
        {
            m_objectWithEvent.Event.Set();
        }

    public:
        T* operator->() const
        {
            return &m_objectWithEvent;
        }

    private:
        ObjectWithEvent<T>& m_objectWithEvent;
    };
}
