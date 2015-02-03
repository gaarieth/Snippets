
#pragma once

class UdpSocket
{
    NO_COPY(UdpSocket);

public:
    explicit UdpSocket(unsigned short);

public:
    bool ReadDatagram(byte*, uint16&, in_addr* pHost = 0, in_port_t* pPort = 0);

    bool SendDatagram(pbyte, uint16, in_addr, in_port_t);

private:
    FileDescriptor m_socket;
};
