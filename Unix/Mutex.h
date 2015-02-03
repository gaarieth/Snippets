
#pragma once

class Mutex
{
    NO_COPY(Mutex);

    friend class Condition;

public:
    Mutex();

    ~Mutex();

public:
    void LockMutex();

    void UnlockMutex();

private:
    pthread_mutex_t m_mutex;
};

struct MutexLock
{
    Mutex& M;

    explicit MutexLock(Mutex&);

    ~MutexLock();
};
