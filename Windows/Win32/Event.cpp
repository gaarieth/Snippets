
#include "StdAfx.h"
#include "Event.h"

using namespace Windows;

CEvent::CEvent(bool manual)
    : m_hEvent(CreateEvent(0, manual, FALSE, 0))
{
}

CEvent::~CEvent(void)
{
    if (m_hEvent)
    {
        CloseHandle(m_hEvent);
    }
}

CEvent::operator HANDLE() const
{
    return m_hEvent;
}

void CEvent::Wait()
{
    if (m_hEvent)
    {
        WaitForSingleObject(m_hEvent, INFINITE);
    }
}

void CEvent::Set()
{
    if (m_hEvent)
    {
        SetEvent(m_hEvent);
    }
}

CAutoResetEvent::CAutoResetEvent(void)
    : CEvent(false)
{
}

CManualResetEvent::CManualResetEvent(void)
    : CEvent(true)
{
}

void CManualResetEvent::Reset()
{
    if (m_hEvent)
    {
        ResetEvent(m_hEvent);
    }
}

bool CManualResetEvent::IsSet() const
{
    return (m_hEvent && (WaitForSingleObject(m_hEvent, 0) == WAIT_OBJECT_0));
}

bool CManualResetEvent::IsNotSet() const
{
    return (m_hEvent && (WaitForSingleObject(m_hEvent, 0) == WAIT_TIMEOUT));
}
