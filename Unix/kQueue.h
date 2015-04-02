
#pragma once

typedef struct kevent kEvent;

extern const kEvent NULL_K_EVENT;

typedef std::vector<kEvent> kEventVector;

int kFilterError(const kEvent&);

int kSocketError(const kEvent&);

class kQueue
{
    NO_COPY(kQueue);

public:
    kQueue(void);

public:
    bool RegisterChange(const kEvent&);

    int WaitForEvents(kEventVector&);

private:
    FileDescriptor m_queue;
};

class kQueuedEvent
{
    NO_COPY(kQueuedEvent);

protected:
    kQueuedEvent
    (
        kQueue&,
        uintptr_t id,
        int16_t filter,
        pvoid udata = 0,
        intptr_t data = 0
    );

    ~kQueuedEvent(void);

public:
    void DisableEvent();

protected:
    void QueueEvent(uint16_t flags, intptr_t data = 0, uint32_t fflags = 0);

public:
    const uintptr_t Id;

    const int16_t Filter;

    const pvoid UserData;

private:
    kQueue& m_queue;
};

struct kReaderEvent : public kQueuedEvent
{
    kReaderEvent(kQueue&, uintptr_t id, pvoid udata = 0);
};

struct kWriterEvent : public kQueuedEvent
{
    kWriterEvent(kQueue&, uintptr_t id, pvoid udata = 0);
};

struct kTimerEvent : public kQueuedEvent
{
    kTimerEvent(kQueue&, uintptr_t id, intptr_t data = 1000);
};

struct kUserEvent : public kQueuedEvent
{
    kUserEvent(kQueue&, uintptr_t id, pvoid udata = 0);

    void TriggerEvent(uint32_t fflags);
};
