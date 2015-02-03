
#include "StdAfx.h"
#include "UdpSocket.h"

UdpSocket::UdpSocket(USHORT port)
    : m_hSocket(socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))
{
    if (!isValidSocket())
        return;

    if (!port)
        return;

    sockaddr_in address =
    {
        AF_INET,
        htons(port)
    };

    {
        BOOL b = TRUE;

        setsockopt(m_hSocket, SOL_SOCKET, SO_EXCLUSIVEADDRUSE, LPCSTR(&b), sizeof(b));
    }

    if (bind(m_hSocket, PSOCKADDR(&address), sizeof(address)))
        CloseSocket();
}

bool UdpSocket::isValidSocket() const
{
    return (m_hSocket != INVALID_SOCKET);
}

UdpSocket::~UdpSocket(void)
{
    CloseSocket();
}

UdpSocket::operator SOCKET() const
{
    return m_hSocket;
}

void UdpSocket::CloseSocket()
{
    if (!isValidSocket())
        return;

    closesocket(m_hSocket);

    m_hSocket = INVALID_SOCKET;
}

bool UdpSocket::ReadDatagram(LPSTR p, WORD& n, PIN_ADDR pHost, PUSHORT pPort)
{
    if (!(p && n && isValidSocket()))
        return (n = 0), false;

    int i = SOCKET_ERROR;

    if (pHost && pPort)
    {
        sockaddr_in address = {0};

        int addressSize = sizeof(address);

        i = recvfrom(m_hSocket, p, n, 0, PSOCKADDR(&address), &addressSize);

        *pHost = address.sin_addr;
        *pPort = ntohs(address.sin_port);
    }
    else
        i = recvfrom(m_hSocket, p, n, 0, 0, 0);

    if (i == SOCKET_ERROR)
    {
        DWORD e = GetLastError();
        // see SIO_UDP_CONNRESET
        return (n = 0), ((e == WSAEWOULDBLOCK) || (e == WSAECONNRESET));
    }
    else
        return (n = i), true;
}

bool UdpSocket::SendDatagram(LPCSTR p, WORD n, IN_ADDR host, USHORT port)
{
    if (!(p && n && host.s_addr && port && isValidSocket()))
        return false;

    sockaddr_in address =
    {
        AF_INET,
        htons(port),
        host
    };

    int i = sendto(m_hSocket, p, n, 0, PSOCKADDR(&address), sizeof(address));

    if (i == SOCKET_ERROR)
        return (GetLastError() == WSAEWOULDBLOCK);
    else
        return (i == n);
}
