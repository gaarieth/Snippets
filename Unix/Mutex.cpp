
#include "Mutex.h"

namespace
{
    const pthread_mutex_t NULL_MUTEX = {0};

    const pthread_mutexattr_t NULL_ATTRIBUTES = {0};
    
    struct MutexAttributes
    {
        pthread_mutexattr_t Attributes;

        MutexAttributes(bool recursive)
            : Attributes(NULL_ATTRIBUTES)
        {
            pthread_mutexattr_init(&Attributes);

            pthread_mutexattr_settype
            (
                &Attributes,
                (recursive ? PTHREAD_MUTEX_RECURSIVE : PTHREAD_MUTEX_NORMAL)
            );
        }

        ~MutexAttributes()
        {
            pthread_mutexattr_destroy(&Attributes);
        }
    };
}

Mutex::Mutex(bool recursive)
    : m_mutex(NULL_MUTEX)
{
    MutexAttributes A(recursive);

    if (pthread_mutex_init(&m_mutex, &A.Attributes))
        m_mutex = NULL_MUTEX;
}

Mutex::~Mutex()
{
    pthread_mutex_destroy(&m_mutex);
}

void Mutex::LockMutex()
{
    pthread_mutex_lock(&m_mutex);
}

void Mutex::UnlockMutex()
{
    pthread_mutex_unlock(&m_mutex);
}

MutexLock::MutexLock(Mutex& m)
    : M(m)
{
    M.LockMutex();
}

MutexLock::~MutexLock()
{
    M.UnlockMutex();
}
