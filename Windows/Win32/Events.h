
#pragma once

class Event
{
    NO_COPY(Event);

protected:
    Event(HANDLE);

    ~Event(void);

public:
    void Wait() const;

    void Set();

    bool isSet() const;

    operator HANDLE() const;

protected:
    const HANDLE m_hEvent;
};

struct ManualResetEvent : public Event
{
    ManualResetEvent();

    void Reset();
};

struct AutoResetEvent : public Event
{
    AutoResetEvent();
};
