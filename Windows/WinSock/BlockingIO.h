
#pragma once

struct BlockingIO
{
    const SOCKET S;
    const HANDLE H;
    const long E;

    BlockingIO(SOCKET s, HANDLE h, long e)
        : S(s)
        , H(h)
        , E(e)
    {
        u_long L = 0;

        if (WSAEventSelect(S, 0, 0) || ioctlsocket(S, FIONBIO, &L))
            DebugBreak();
    }

    ~BlockingIO()
    {
        if (WSAEventSelect(S, H, E))
            DebugBreak();
    }
};
