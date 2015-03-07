
#include "TcpSockets.h"

TcpSocket::TcpSocket(void)
    : m_socket(socket(AF_INET, SOCK_STREAM/*| SOCK_NONBLOCK*/, IPPROTO_TCP))
{
    m_socket.MarkAsNonBlocking();
}

TcpSocket::TcpSocket(int socketDescriptor)
    : m_socket(socketDescriptor)
{
}

TcpSocket::~TcpSocket(void)
{
}

const FileDescriptor& TcpSocket::GetSocketDescriptor() const
{
    return m_socket;
}

TcpListener::TcpListener(unsigned short p)
{
    if (!m_socket.isValid())
        return;

    sockaddr_in address =
    {
        #ifdef __APPLE__ // TODO: BSD?
        sizeof(sockaddr_in),
        #endif
        AF_INET,
        htons(p)
    };

    const int d = m_socket.GetDescriptor();

    {
        int i = 1;

        setsockopt(d, SOL_SOCKET, SO_REUSEADDR, &i, sizeof(i));
    }

    // TODO: address.sin_len

    if (bind(d, (sockaddr*) &address, address.sin_len) || listen(d, SOMAXCONN))
        m_socket.CloseDescriptor();
}

int TcpListener::AcceptConnection()
{
    const int d = m_socket.GetDescriptor();

    while (true)
    {
#ifdef __APPLE__
        int i = accept(d, 0, 0);
#else
        int i = accept4(d, 0, 0, SOCK_NONBLOCK);
#endif
        if ((i == -1) && (errno == EINTR))
            continue;
        return i;
    }
}

TcpClient::TcpClient(const char* ip, unsigned short p)
{
    if (!m_socket.isValid())
        return;

    sockaddr_in address =
    {
        #ifdef __APPLE__ // TODO: BSD?
        sizeof(sockaddr_in),
        #endif
        AF_INET,
        htons(p),
        inet_addr(ip)
    };

    const int d = m_socket.GetDescriptor();

    while (true)
    {
        int i = connect(d, (sockaddr*) &address, address.sin_len);

        if (i == -1)
        {
            int e = errno;

            if (e == EINTR)
                continue;

            if (e != EINPROGRESS)
                m_socket.CloseDescriptor();
        }

        break;
    } // while
}

TcpClient::TcpClient(int socketDescriptor)
    : TcpSocket(socketDescriptor)
{
}

TcpClient::~TcpClient(void)
{
    if (m_socket.isValid())
        shutdown(m_socket.GetDescriptor(), SHUT_WR);
}
