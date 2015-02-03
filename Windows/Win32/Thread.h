
#pragma once

namespace Windows
{
    class CThread
    {
        NO_COPY(CThread);

    public:
        CThread(LPTHREAD_START_ROUTINE, LPVOID);

        ~CThread(void);

    public:
        static void SetName(LPCSTR);

    private:
        const HANDLE m_hThread;
    };
}
