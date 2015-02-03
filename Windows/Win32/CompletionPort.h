
#pragma once

namespace Windows
{
    class CThreadPool;

    struct CompletionStatus
    {
        DWORD        BytesTransferred;
        ULONG_PTR    CompletionKey;
        LPOVERLAPPED pOperation;

        operator bool() const;
    };

    typedef void (*CompletionRoutine)(const CompletionStatus&, LPVOID);

    class CCompletionPort
    {
        NO_COPY(CCompletionPort);

    public:
        CCompletionPort(CompletionRoutine, LPVOID completionRoutineParameter);

        ~CCompletionPort(void);

    public:
        void AttachHandle(HANDLE, ULONG_PTR completionKey);

        void PostCompletionStatus(const CompletionStatus&);

    private:
        bool GetCompletionStatus(CompletionStatus&) const;

    private:
        static DWORD WINAPI CompletionThreadRoutine(LPVOID);

    private:
        const HANDLE m_hPort;

        const CompletionRoutine m_completionRoutine;

        const LPVOID m_completionRoutineParameter;

        const CThreadPool* m_pThreadPool;
    };
}
