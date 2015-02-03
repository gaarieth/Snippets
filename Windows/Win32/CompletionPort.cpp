
#include "StdAfx.h"
#include "CompletionPort.h"
#include "ThreadPool.h"
#include "Thread.h"

using namespace Windows;

CompletionStatus::operator bool() const
{
    return (BytesTransferred || CompletionKey || pOperation);
}

void CCompletionPort::AttachHandle(HANDLE h, ULONG_PTR completionKey)
{
    CreateIoCompletionPort(h, m_hPort, completionKey, 0);
}

CCompletionPort::CCompletionPort(CompletionRoutine completionRoutine,
                                 LPVOID completionRoutineParameter)
    : m_hPort(CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0))
    , m_completionRoutine(completionRoutine)
    , m_completionRoutineParameter(completionRoutineParameter)
    , m_pThreadPool(new CThreadPool(CompletionThreadRoutine, this))
{
}

CCompletionPort::~CCompletionPort(void)
{
    CompletionStatus completionStatus = {0};

    for (BYTE i = 0; i < m_pThreadPool->Size; i++)
    {
        PostCompletionStatus(completionStatus);
    }

    delete m_pThreadPool;

    CloseHandle(m_hPort);
}

void CCompletionPort::PostCompletionStatus(const CompletionStatus& completionStatus)
{
    PostQueuedCompletionStatus(m_hPort,
                               completionStatus.BytesTransferred,
                               completionStatus.CompletionKey,
                               completionStatus.pOperation);
}

bool CCompletionPort::GetCompletionStatus(CompletionStatus& completionStatus) const
{
    return (GetQueuedCompletionStatus(m_hPort,
                                      &completionStatus.BytesTransferred,
                                      &completionStatus.CompletionKey,
                                      &completionStatus.pOperation,
                                      INFINITE) != 0);
}

  // static
DWORD WINAPI CCompletionPort::CompletionThreadRoutine(LPVOID pv)
{
    CThread::SetName("CompletionPort");

    CCompletionPort* const self = static_cast<CCompletionPort*>(pv);

    while (true)
    {
        CompletionStatus completionStatus = {0};

        if (self->GetCompletionStatus(completionStatus))
        {
            if (completionStatus)
            {
                self->m_completionRoutine(completionStatus,
                                          self->m_completionRoutineParameter);
            }
            else
            {
                return 0;
            }
        }
        else if (completionStatus.pOperation)
        {
            completionStatus.BytesTransferred = 0;

            self->m_completionRoutine(completionStatus,
                                      self->m_completionRoutineParameter);
        }
        else
            DebugBreak();
    }
}
