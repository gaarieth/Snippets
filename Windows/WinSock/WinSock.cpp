
#include "StdAfx.h"
#include "WinSock.h"

WinSock::WinSock(void)
{
    WSADATA wsaData = {0};

    WSAStartup(WINSOCK_VERSION, &wsaData);
}

WinSock::~WinSock(void)
{
    WSACleanup();
}
