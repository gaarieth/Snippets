
#include "Condition.h"
#include "Mutex.h"

static const pthread_cond_t NULL_CONDITION = {0};

Condition::Condition(Mutex& mutex)
    : m_bool(false)
    , m_mutex(mutex)
    , m_condition(NULL_CONDITION)
{
    pthread_cond_init(&m_condition, 0);
}

Condition::~Condition()
{
    pthread_cond_destroy(&m_condition);
}

Condition::operator bool() const
{
    return m_bool;
}

void Condition::WaitForSignal()
{
    MutexLock lock(m_mutex);

    while (!m_bool)
        pthread_cond_wait(&m_condition, &m_mutex.m_mutex);

    // TODO: m_bool = false;
}

void Condition::SignalOneThread()
{
    MutexLock lock(m_mutex);

    m_bool = true;

    pthread_cond_signal(&m_condition);
}

void Condition::SignalAllThreads()
{
    MutexLock lock(m_mutex);

    m_bool = true;

    pthread_cond_broadcast(&m_condition);
}
