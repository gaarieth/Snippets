
#pragma once

#include <libkern/OsAtomic.h>

struct ReferenceCount
{
    volatile int References;

    ReferenceCount()
        : References(1)
    {
    }

    void IncrementReferences()
    {
        OSAtomicIncrement32(&References);
    }

    int DecrementReferences()
    {
        return OSAtomicDecrement32(&References);
    }
};
