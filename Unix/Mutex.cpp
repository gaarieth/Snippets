
#include "Mutex.h"

static const pthread_mutex_t NULL_MUTEX = {0};

Mutex::Mutex()
    : m_mutex(NULL_MUTEX)
{
    if (pthread_mutex_init(&m_mutex, 0))
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
