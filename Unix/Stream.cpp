
#include "Stream.h"

Stream::Stream(const FileDescriptor& descriptor)
    : m_descriptor(descriptor)
{
}

bool Stream::ExtractBytes(byte* p, uint16& n)
{
    int e = 0;

    ssize_t i = ReadBytes(p, n, e);

    if (i > 0)
    {
        n = i;

        return true;
    }
    else
        n = 0;

    if (i == 0)
        return false;

    return ((e == EAGAIN) || (e == EWOULDBLOCK));
}

bool Stream::InsertBytes(pbyte p, uint16& n)
{
    int e = 0;

    ssize_t i = SendBytes(p, n, e);

    if (i > 0)
    {
        n = i;

        return true;
    }
    else
        n = 0;

    if (i == 0)
        return false;

    return ((e == EAGAIN) || (e == EWOULDBLOCK));
}

ssize_t Stream::ReadBytes(byte* p, uint16 n, int& e)
{
    if (!(p && n && m_descriptor.isValid()))
        return 0;

    while (true)
    {
        ssize_t i = read(m_descriptor.GetDescriptor(), p, n);

        e = errno;

        if ((i == -1) && (e == EINTR))
            continue;

        return i;
    }
}

ssize_t Stream::SendBytes(pbyte p, uint16 n, int& e)
{
    if (!(p && n && m_descriptor.isValid()))
        return 0;

    while (true)
    {
        ssize_t i = write(m_descriptor.GetDescriptor(), p, n);

        e = errno;

        if ((i == -1) && (e == EINTR))
            continue;

        return i;
    }
}
