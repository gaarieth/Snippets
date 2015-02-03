
#pragma once

class UdpSocket
{
    NO_COPY(UdpSocket);

public:
    UdpSocket(USHORT port = 0);

    ~UdpSocket(void);

public:
    bool isValidSocket() const;

    operator SOCKET() const;

    bool ReadDatagram(LPSTR, WORD&, PIN_ADDR pHost = 0, PUSHORT pPort = 0);

    bool SendDatagram(LPCSTR, WORD, IN_ADDR host, USHORT port);

private:
    void CloseSocket();

private:
    SOCKET m_hSocket;
};
