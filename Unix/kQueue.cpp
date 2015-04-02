
#include "kQueue.h"

const kEvent NULL_K_EVENT = {0};

int kFilterError(const kEvent& e)
{
    return ((e.flags & EV_ERROR) ? int(e.data) : 0);
}

int kSocketError(const kEvent& e)
{
    return ((e.flags & EV_EOF) ? int(e.fflags) : 0);
}

kQueue::kQueue(void)
    : m_queue(kqueue())
{
}

bool kQueue::RegisterChange(const kEvent& change)
{
    return
    (
        m_queue.isValid() &&
        (kevent(m_queue.GetDescriptor(), &change, 1, 0, 0, 0) == 0)
    );
}

int kQueue::WaitForEvents(kEventVector& events)
{
    const int nEvents = int(events.size());

    return
    (
        ((nEvents > 0) && m_queue.isValid()) ? kevent
        (
            m_queue.GetDescriptor(),
            0,
            0,
            &events[0],
            nEvents,
            0
        ) : 0
    );
}

kQueuedEvent::kQueuedEvent
(
    kQueue& queue,
    uintptr_t id,
    int16_t filter,
    pvoid udata,
    intptr_t data
)
    : m_queue(queue)
    , Id(id)
    , Filter(filter)
    , UserData(udata)
{
    QueueEvent(EV_ADD | EV_CLEAR, data);
}

kQueuedEvent::~kQueuedEvent(void)
{
    QueueEvent(EV_DELETE);
}

void kQueuedEvent::DisableEvent()
{
    QueueEvent(EV_DISABLE);
}

void kQueuedEvent::QueueEvent(uint16_t flags, intptr_t data, uint32_t fflags)
{
    kEvent e =
    {
        Id,
        Filter,
        flags,
        fflags,
        data,
        UserData
    };

    m_queue.RegisterChange(e);
}

kReaderEvent::kReaderEvent(kQueue& queue, uintptr_t id, pvoid udata)
    : kQueuedEvent(queue, id, EVFILT_READ, udata)
{
}

kWriterEvent::kWriterEvent(kQueue& queue, uintptr_t id, pvoid udata)
    : kQueuedEvent(queue, id, EVFILT_WRITE, udata)
{
}

kTimerEvent::kTimerEvent(kQueue& queue, uintptr_t id, intptr_t data)
    : kQueuedEvent(queue, id, EVFILT_TIMER, 0, data)
{
}

kUserEvent::kUserEvent(kQueue& queue, uintptr_t id, pvoid udata)
    : kQueuedEvent(queue, id, EVFILT_USER, udata)
{
}

void kUserEvent::TriggerEvent(uint32_t fflags)
{
    QueueEvent(0, 0, NOTE_FFOR | NOTE_TRIGGER | fflags);
}
