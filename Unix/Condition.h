
#pragma once

class Mutex;

class Condition
{
    NO_COPY(Condition);

public:
    explicit Condition(Mutex&);

    ~Condition();

public:
    operator bool() const;

public:
    void WaitForSignal();

    void SignalOneThread();

    void SignalAllThreads();

private:
    bool m_bool;

    Mutex& m_mutex;

    pthread_cond_t m_condition;
};
