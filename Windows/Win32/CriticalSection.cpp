
#include "StdAfx.h"
#include "CriticalSection.h"

using namespace Windows;

CLock::CLock(void)
{
    InitializeCriticalSection(&m_criticalSection);
}

CLock::~CLock(void)
{
    DeleteCriticalSection(&m_criticalSection);
}

void CLock::Enter()
{
    EnterCriticalSection(&m_criticalSection);
}

void CLock::Leave()
{
    LeaveCriticalSection(&m_criticalSection);
}

CAutoLock::CAutoLock(CLock& lock)
    : m_lock(lock)
{
    m_lock.Enter();
}

CAutoLock::~CAutoLock(void)
{
    m_lock.Leave();
}
