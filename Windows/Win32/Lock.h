
#pragma once

class Lock
{
    NO_COPY(Lock);

public:
    Lock(void);

    ~Lock(void);

public:
    void Enter();

    void Leave();

private:
    CRITICAL_SECTION criticalSection;
};

struct AutoLock
{
    Lock& L;

    AutoLock(Lock&);

    ~AutoLock(void);
};
