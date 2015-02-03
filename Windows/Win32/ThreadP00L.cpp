
#include "StdAfx.h"
#include "ThreadPool.h"

using namespace Windows;

CThreadPool::CThreadPool(LPTHREAD_START_ROUTINE p, LPVOID pv)
    : m_threads(0)
    , Size(m_threads.length)
{
    SYSTEM_INFO si = {0};

    GetNativeSystemInfo(&si);

    m_threads.Resize(2 * si.dwNumberOfProcessors);

    for (BYTE i = 0; i < m_threads.length; i++)
    {
        m_threads[i] = CreateThread(0, 0, p, pv, 0, 0);
    }
}

CThreadPool::~CThreadPool()
{
    WaitForMultipleObjects(m_threads.length, m_threads.GetArray(), TRUE, INFINITE);

    for (BYTE i = 0; i < m_threads.length; i++)
    {
        CloseHandle(m_threads[i]);
    }
}
