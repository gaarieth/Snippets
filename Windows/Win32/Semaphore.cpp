
#include "StdAfx.h"
#include "Semaphore.h"

Semaphore::Semaphore(long initial, long maximum)
    : m_hSemaphore(CreateSemaphore(0, initial, maximum, 0))
{
}

Semaphore::~Semaphore()
{
    CloseHandle(m_hSemaphore);
}

void Semaphore::Wait() const
{
    WaitForSingleObject(m_hSemaphore, INFINITE);
}

void Semaphore::Post()
{
    ReleaseSemaphore(m_hSemaphore, 1, 0);
}
