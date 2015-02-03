
#pragma once

namespace Windows
{
    class CThreadPool
    {
        NO_COPY(CThreadPool);

    public:
        CThreadPool(LPTHREAD_START_ROUTINE, LPVOID);

        ~CThreadPool(void);

    private:
        CArray<HANDLE> m_threads;

    public:
        const BYTE& Size;
    };
}
