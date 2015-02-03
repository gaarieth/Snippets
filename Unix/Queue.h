
#pragma once

#include "Semaphore.h"
#include "Mutex.h"

template <class T, int N = 1000>
class Queue
{
public:
    #ifdef __APPLE__
    Queue(const char* P, const char* C)
        : Produced(P, 0)
        , Consumed(C, N)
    {
    }
    #else
    Queue()
        : Produced(0)
        , Consumed(N)
    {
    }
    #endif
    void PushBack(const T& t)
    {
        Consumed.Wait();
        {
            MutexLock Lock(SlotsMutex);
            Slots.push_back(t);
        }
        Produced.Post();
    }

    void PopFront(T& t)
    {
        Produced.Wait();
        {
            MutexLock Lock(SlotsMutex);
            t = Slots.front();
            Slots.pop_front();
        }
        Consumed.Post();
    }

private:
    std::deque<T> Slots;
    Semaphore Produced;
    Semaphore Consumed;
    Mutex SlotsMutex;
};
