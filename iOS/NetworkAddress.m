
#import "NetworkAddress.h"
#import <arpa/inet.h>
#import <net/if.h>
#import <ifaddrs.h>

@implementation NetworkAddress

+ (NSString*) ipAddressFromSocketAddress: (const struct sockaddr*) socketAddress
{
    sa_family_t family = socketAddress->sa_family;

    const void* address = 0;
    in_port_t port = 0;

    if (family == AF_INET)
    {
        const struct sockaddr_in* p
            = (const struct sockaddr_in*) socketAddress;
        address = &p->sin_addr.s_addr;
        port = ntohs(p->sin_port);
    }
    else if (family == AF_INET6)
    {
        const struct sockaddr_in6* p
            = (const struct sockaddr_in6*) socketAddress;
        address = &p->sin6_addr.s6_addr;
        port = ntohs(p->sin6_port);
    }

    if (!address)
        return nil;

    char c[INET6_ADDRSTRLEN] = {0};
    if (!inet_ntop(family, address, c, sizeof(c)))
        return nil;

    return (port
            ? [NSString stringWithFormat: @"%s:%u", c, port]
            : [NSString stringWithFormat: @"%s", c]);
}

+ (NSArray*) allAddresses
{
    NSMutableArray* addresses = [NSMutableArray array];

    struct ifaddrs* interfaces = 0;

    if (getifaddrs(&interfaces))
        return nil;

    for (struct ifaddrs* interface = interfaces;
         interface;
         interface = interface->ifa_next)
    {
        if (!interface->ifa_addr)
            continue;

        if (interface->ifa_flags & IFF_LOOPBACK)
            continue;
        
        if (!(interface->ifa_flags & IFF_UP))
            continue;

        NSString* ipAddress =
            [self ipAddressFromSocketAddress: interface->ifa_addr];

        if (!ipAddress)
            continue;

        [addresses addObject: ipAddress];
    } // for

    freeifaddrs(interfaces);

    return addresses;
}

+ (NSString*) ipAddressOfPeer: (NSFileHandle*) peer
{
    struct sockaddr socketAddress = {sizeof(struct sockaddr)};

    socklen_t addressLength = socketAddress.sa_len;

    int socketHandle = peer.fileDescriptor;

    if (getpeername(socketHandle, &socketAddress, &addressLength))
        return nil;

    if (socketAddress.sa_family == AF_INET)
    {
        struct sockaddr_in socketAddressV4 = {sizeof(struct sockaddr_in)};
        addressLength = socketAddressV4.sin_len;
        struct sockaddr* p = (struct sockaddr*) &socketAddressV4;
        if (getpeername(socketHandle, p, &addressLength))
            return nil;
        return [self ipAddressFromSocketAddress: p];
    }
    else if (socketAddress.sa_family == AF_INET6)
    {
        struct sockaddr_in6 socketAddressV6 = {sizeof(struct sockaddr_in6)};
        addressLength = socketAddressV6.sin6_len;
        struct sockaddr* p = (struct sockaddr*) &socketAddressV6;
        if (getpeername(socketHandle, p, &addressLength))
            return nil;
        return [self ipAddressFromSocketAddress: p];
    }

    return nil;
}

@end
