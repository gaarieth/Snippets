
#pragma once

class Semaphore
{
    NO_COPY(Semaphore);

public:
    Semaphore(long initial, long maximum);

    ~Semaphore();

public:
    void Wait() const;

    void Post();

private:
    HANDLE m_hSemaphore;
};
