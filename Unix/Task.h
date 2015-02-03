
#pragma once

typedef pvoid (*TaskFunction)(pvoid);

class Task
{
    NO_COPY(Task);

public:
    explicit Task(TaskFunction F, pvoid p = 0)
        : m_taskId(0)
    {
        if (F && pthread_create(&m_taskId, 0, F, p))
            m_taskId = 0;
    }

    ~Task()
    {
        if (m_taskId)
            pthread_join(m_taskId, 0);
    }

private:
    pthread_t m_taskId;
};

template <int N = 2>
class TaskPool
{
    NO_COPY(TaskPool);

public:
    explicit TaskPool(TaskFunction F, pvoid p = 0)
        : PoolSize(N)
    {
        for (int i = 0; i < N; i++)
            m_tasks[i] = new Task(F, p);
    }

    ~TaskPool()
    {
        int i = N;

        while (i --> 0)
            delete m_tasks[i];
    }

public:
    const int PoolSize;

private:
    Task* m_tasks[N];
};
