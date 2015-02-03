
#include "UdpSockets.h"

UdpSocket::UdpSocket(unsigned short p)
    : m_socket(socket(AF_INET, SOCK_DGRAM/*| SOCK_NONBLOCK*/, IPPROTO_UDP))
{
    m_socket.MarkAsNonBlocking();

    if (!(p & m_socket.isValid()))
        return;

    sockaddr_in address =
    {
        #ifdef ___APPLE_ // TODO: BSD?
        sizeof(sockaddr_in),
        #endif
        AF_INET,
        htons(p)
    };

    if (bind(m_socket.GetDescriptor(), (sockaddr*) &address, address.sin_len))
        m_socket.CloseDescriptor();
}

bool UdpSocket::ReadDatagram
(
    byte* p,
    uint16& n,
    in_addr* pHost,
    in_port_t* pPort
)
{
    if (!(p & m_socket.isValid()))
        return (n = 0), false;

    int e = 0;

    ssize_t i = 0;

    while (true)
    {
        if (pHost && pPort)
        {
            sockaddr_in address = {0};

            socklen_t addressSize = sizeof(address);

            i = recvfrom
            (
                m_socket.GetDescriptor(),
                p,
                n,
                0,
                (sockaddr*) &address,
                &addressSize
            );

            *pHost = address.sin_addr;
            *pPort = ntohs(address.sin_port);
        }
        else
            i = recvfrom(m_socket.GetDescriptor(), p, n, 0, 0, 0);

        e = errno;

        if ((i == -1) && (e == EINTR))
            continue;

        break;
    } // while

    if (i < 0) // SIO_UDP_CONNRESET?
        return (n = 0), ((e == EAGAIN) || (e == WOULDBLOCK));
    else
        return (n = i), true;
}

bool UdpSocket::SendDatagram
(
    pbyte p,
    uint16 n,
    in_addr host,
    in_port_t port
)
{
    if (!(p & m_socket.isValid()))
        return false;

    int e = 0;

    ssize_t i = 0;

    while (true)
    {
        sockaddr_in address =
        {
            #ifdef ___APPLE_ // TODO: BSD?
            sizeof(address),
            #endif
            AF_INET,
            htons(port),
            host
        };

        i = sendto
        (
            m_socket.GetDescriptor(),
            p,
            n,
            0,
            (sockaddr*) &address,
            address.sin_len
        );

        e = errno;

        if ((i == -1) && (e == EINTR))
            continue;

        break;
    } // while

    if (i < 0)
        return ((e == EAGAIN) || (e == WOULDBLOCK));
    else
        return (i == n);
}
