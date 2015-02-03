
#include "StdAfx.h"
#include "Thread.h"

using namespace Windows;

namespace
{
    const DWORD MS_VC_EXCEPTION = 0x406D1388;

    #pragma pack (push, 8)
    struct ThreadName
    {
        DWORD Type;
        LPCSTR Name;
        DWORD Id;
        DWORD Flags;
    };
    #pragma pack (pop)
}

CThread::CThread(LPTHREAD_START_ROUTINE p, LPVOID pv)
    : m_hThread(CreateThread(0, 0, p, pv, 0, 0))
{
}

CThread::~CThread(void)
{
    WaitForSingleObject(m_hThread, INFINITE);
    // _snwprintf_s
    CloseHandle(m_hThread);
}

void CThread::SetName(LPCSTR s)
{
    if (!(s && s[0]))
    {
        return;
    }

    ThreadName threadName =
    {
        0x1000,
        s,
        -1,
        0
    };

    __try
    {
        RaiseException(MS_VC_EXCEPTION,
                       0,
                       sizeof(threadName) / sizeof(ULONG_PTR),
                       PULONG_PTR(&threadName));
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
    }
}
