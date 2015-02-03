
#pragma once

template
<
    WORD ReadBufferSize,
    WORD SendBufferSize
>
struct TcpStream
{
    const SOCKET Socket;

    char ReadBuffer[ReadBufferSize + 1]; WORD ReadOffset;
    char SendBuffer[SendBufferSize + 1]; WORD SendOffset;

    TcpStream(SOCKET s)
        : Socket(s)
        , ReadOffset(0)
        , SendOffset(0)
    {
        ZeroMemory(ReadBuffer, sizeof(ReadBuffer));
        ZeroMemory(SendBuffer, sizeof(SendBuffer));
    }

    bool ReadBytes()
    {
        while (ReadOffset < sizeof(ReadBuffer) - 1)
        {
            int i = recv
            (
                Socket,
                ReadBuffer + ReadOffset,
                sizeof(ReadBuffer) - ReadOffset - 1,
                0
            );
            if (i < 1)
                return ((i == 0) || (GetLastError() == WSAEWOULDBLOCK));
            ReadBuffer[ReadOffset += i] = 0;
        } // while
        return true;
    }

    bool SendBytes()
    {
        while (SendOffset)
        {
            int i = send(Socket, SendBuffer, SendOffset, 0);
            if (i < 1)
                return (GetLastError() == WSAEWOULDBLOCK);
            memmove(SendBuffer, SendBuffer + i, SendOffset -= i);
        } // while
        return true;
    }

    bool CanRead() const
    {
        return (sizeof(ReadBuffer) - ReadOffset > 1);
    }

    bool CanSend() const
    {
        return (sizeof(SendBuffer) - SendOffset > 1);
    }

    WORD ReadCapacity() const
    {
        return (sizeof(ReadBuffer) - ReadOffset - 1);
    }

    WORD SendCapacity() const
    {
        return (sizeof(SendBuffer) - SendOffset - 1);
    }
};
