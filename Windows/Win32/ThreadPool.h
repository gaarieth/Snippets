
#pragma once

template <BYTE N>
class ThreadPool
{
    NO_COPY(ThreadPool);

public:
    ThreadPool(LPTHREAD_START_ROUTINE f, LPVOID p)
    {
        for (BYTE i = 0; i < N; i++)
            hThreads[i] = CreateThread(0, 0, f, p, 0, 0);
    }

    ThreadPool(LPTHREAD_START_ROUTINE (&f)[N], LPVOID p)
    {
        for (BYTE i = 0; i < N; i++)
            hThreads[i] = CreateThread(0, 0, f[i], p, 0, 0);
    }

    ~ThreadPool(void)
    {
        WaitForMultipleObjects(N, hThreads, TRUE, INFINITE);

        for (BYTE i = 0; i < N; i++)
            CloseHandle(hThreads[i]);
    }

private:
    HANDLE hThreads[N];
};
