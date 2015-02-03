
#include "StdAfx.h"
#include "Events.h"

Event::Event(HANDLE h)
    : m_hEvent(h)
{
}

Event::~Event(void)
{
    if (m_hEvent)
        CloseHandle(m_hEvent);
}

void Event::Wait() const
{
    if (m_hEvent)
        WaitForSingleObject(m_hEvent, INFINITE);
}

void Event::Set()
{
    if (m_hEvent)
        SetEvent(m_hEvent);
}

bool Event::isSet() const
{
    return (m_hEvent && (WaitForSingleObject(m_hEvent, 0) == WAIT_OBJECT_0));
}

Event::operator HANDLE() const
{
    return m_hEvent;
}

ManualResetEvent::ManualResetEvent()
    : Event(CreateEvent(0, TRUE, FALSE, 0))
{
}

void ManualResetEvent::Reset()
{
    if (m_hEvent)
        ResetEvent(m_hEvent);
}

AutoResetEvent::AutoResetEvent()
    : Event(CreateEvent(0, FALSE, FALSE, 0))
{
}
