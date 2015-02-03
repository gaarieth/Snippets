
#pragma once

#include "Semaphore.h"
#include "Lock.h"

template <class T, int N>
class Queue
{
    NO_COPY(Queue);

public:
    Queue()
        : Produced(0, N)
        , Consumed(N, N)
    {
    }

public:
    void PushBack(const T& t)
    {
        Consumed.Wait();
        {
            AutoLock autoLock(SlotsLock);
            Slots.push_back(t);
        }
        Produced.Post();
    }

    void PopFront(T& t)
    {
        Produced.Wait();
        {
            AutoLock autoLock(SlotsLock);
            t = Slots.front();
            Slots.pop_front();
        }
        Consumed.Post();
    }

private:
    Lock SlotsLock;
    std::deque<T> Slots;
    Semaphore Produced;
    Semaphore Consumed;
};
