
#include "StdAfx.h"
#include "TcpSocket.h"

TcpSocket::TcpSocket(void)
    : m_hSocket(socket(AF_INET, SOCK_STREAM, IPPROTO_TCP))
{
}

TcpSocket::~TcpSocket(void)
{
    CloseSocket();
}

bool TcpSocket::isValidSocket() const
{
    return (m_hSocket != INVALID_SOCKET);
}

TcpSocket::operator SOCKET() const
{
    return m_hSocket;
}

bool TcpSocket::Connect(LPCSTR host, USHORT port)
{
    if (!(host && host[0] && port && isValidSocket()))
        return false;

    sockaddr_in address =
    {
        AF_INET,
        htons(port)
    };

    address.sin_addr.s_addr = inet_addr(host);

    if (connect(m_hSocket, PSOCKADDR(&address), sizeof(address)))
    {
        if (GetLastError() == WSAEWOULDBLOCK)
            return true;

        CloseSocket();

        return false;
    }

    return true;
}

void TcpSocket::CloseSocket()
{
    if (!isValidSocket())
        return;

    shutdown(m_hSocket, SD_SEND);

    closesocket(m_hSocket);

    m_hSocket = INVALID_SOCKET;
}
