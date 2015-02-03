
#pragma once

class Semaphore
{
    NO_COPY(Semaphore);

public:
    ~Semaphore();

public:
    operator bool() const;

public:
    void Wait();

    void Post();

#ifdef __APPLE__
public:
    Semaphore(const char*, unsigned);

private:
    const char* m_name;

    sem_t* m_semaphore;
#else
public:
    explicit Semaphore(unsigned);

private:
    sem_t m_semaphore;
#endif
};
