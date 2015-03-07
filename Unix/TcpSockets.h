
#pragma once

class TcpSocket
{
    NO_COPY(TcpSocket);

public:
    virtual ~TcpSocket(void);

protected:
    TcpSocket(void);

    explicit TcpSocket(int socketDescriptor);

public:
    const FileDescriptor& GetSocketDescriptor() const;

protected:
    FileDescriptor m_socket;
};

struct TcpListener : public TcpSocket
{
    explicit TcpListener(unsigned short);

    int AcceptConnection();
};

struct TcpClient : public TcpSocket
{
    TcpClient(const char*, unsigned short);

    explicit TcpClient(int socketDescriptor);

    ~TcpClient(void);
};

typedef std::set<TcpClient*> TcpClientSet;
