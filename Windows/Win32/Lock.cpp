
#include "StdAfx.h"
#include "Lock.h"

Lock::Lock(void)
{
    InitializeCriticalSection(&criticalSection);
}

Lock::~Lock(void)
{
    DeleteCriticalSection(&criticalSection);
}

void Lock::Enter()
{
    EnterCriticalSection(&criticalSection);
}

void Lock::Leave()
{
    LeaveCriticalSection(&criticalSection);
}

AutoLock::AutoLock(Lock& l)
    : L(l)
{
    L.Enter();
}

AutoLock::~AutoLock(void)
{
    L.Leave();
}
