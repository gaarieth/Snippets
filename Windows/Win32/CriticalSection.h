
#pragma once

namespace Windows
{
    class CLock
    {
        NO_COPY(CLock);

    public:
        CLock(void);

        ~CLock(void);

    public:
        void Enter();

        void Leave();

    private:
        CRITICAL_SECTION m_criticalSection;
    };

    class CAutoLock
    {
        NO_COPY(CAutoLock);

    public:
        explicit CAutoLock(CLock&);

        ~CAutoLock(void);

    private:
        CLock& m_lock;
    };

    template <class T>
    struct ObjectWithLock : public T
    {
        CLock Lock;
    };

    template <class T>
    class CObjectWithLockPtr
    {
        NO_COPY(CObjectWithLockPtr);

    public:
        explicit CObjectWithLockPtr(ObjectWithLock<T>& objectWithLock)
            : m_objectWithLock(objectWithLock)
        {
            m_objectWithLock.Lock.Enter();
        }

        ~CObjectWithLockPtr(void)
        {
            m_objectWithLock.Lock.Leave();
        }

    public:
        T* operator->() const
        {
            return &m_objectWithLock;
        }

    private:
        ObjectWithLock<T>& m_objectWithLock;
    };
}
