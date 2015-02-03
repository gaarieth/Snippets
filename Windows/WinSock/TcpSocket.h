
#pragma once

class TcpSocket
{
public:
    TcpSocket(void);

    ~TcpSocket(void);

public:
    bool isValidSocket() const;

    operator SOCKET() const;

    bool Connect(LPCSTR ipAddress, USHORT port);

private:
    void CloseSocket();

private:
    SOCKET m_hSocket;
};
