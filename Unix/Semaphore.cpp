
#include "Semaphore.h"

#ifdef __APPLE__
Semaphore::Semaphore(const char* s, unsigned i)
    : m_semaphore(SEM_FAILED)
    , m_name(0)
{
    if (!(s && s[0]))
        return;

    m_name = s;

    sem_unlink(m_name); // ???

    m_semaphore = sem_open(m_name, O_CREAT | O_EXCL, 0600, i);
}

Semaphore::operator bool() const
{
    return (m_semaphore != SEM_FAILED);
}
#else
Semaphore::Semaphore(unsigned i)
    : m_semaphore(0)
{
    sem_init(&m_semaphore, 0, i);
}
#endif

Semaphore::~Semaphore()
{
    #ifdef __APPLE__
    if (static_cast<bool>(*this))
    {
        sem_close(m_semaphore);
        sem_unlink(m_name);
    }
    #else
    sem_destroy(&m_semaphore);
    #endif
}

void Semaphore::Wait()
{
    while (true)
    {
        #ifdef __APPLE__
        int i = sem_wait(m_semaphore);
        #else
        int i = sem_wait(&m_semaphore);
        #endif
        if ((i == -1) && (errno == EINTR))
            continue;
        break;
    }
}

void Semaphore::Post()
{
    #ifdef __APPLE__
    sem_post(m_semaphore);
    #else
    sem_post(&m_semaphore);
    #endif
}
