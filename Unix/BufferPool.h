
#pragma once

#include "ByteVector.h"
#include "ObjectPool.h"

typedef ByteVector Buffer;

template <int N = 1000>
struct BufferAllocator
{
    static Buffer* CreateObject()
    {
        return new Buffer(N, 0);
    }

    static void DeleteObject(Buffer* pBuffer)
    {
        delete pBuffer;
    }
};

typedef ObjectPool< Buffer, BufferAllocator<> > BufferPool;
