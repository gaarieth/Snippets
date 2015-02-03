
#pragma once

#include "Semaphore.h"
#include "Mutex.h"

template <class T, class A>
class ObjectPool
{
    NO_COPY(ObjectPool);

public:
    #ifdef __APPLE__
    ObjectPool(const char* poolName, int poolSize = 1000)
        : PoolSemaphore(poolName, poolSize)
    #else
    explicit ObjectPool(int poolSize = 1000)
        : PoolSemaphore(poolSize)
    #endif
    {
        for (int i = 0; i < poolSize; i++)
            Pool.push_back(A::CreateObject());
    }

    ~ObjectPool()
    {
        while (!Pool.empty())
        {
            A::DeleteObject(Pool.front());
            Pool.pop_front();
        }
    }

public:
    T* GetPooledObject()
    {
        T* pT = 0;
        PoolSemaphore.Wait();
        {
            MutexLock Lock(PoolMutex);
            pT = Pool.front();
            Pool.pop_front();
        }
        return pT;
    }

    void PutPooledObject(T* pT)
    {
        {
            MutexLock Lock(PoolMutex);
            Pool.push_back(pT);
        }
        PoolSemaphore.Post();
    }

private:
    std::deque<T*> Pool;
    Semaphore PoolSemaphore;
    Mutex PoolMutex;
};
