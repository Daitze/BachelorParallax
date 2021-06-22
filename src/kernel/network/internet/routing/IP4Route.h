//
// Created by hannes on 15.05.21.
//

#ifndef HHUOS_IP4ROUTE_H
#define HHUOS_IP4ROUTE_H


#include <kernel/network/internet/addressing/IP4Address.h>
#include <kernel/network/internet/addressing/IP4Netmask.h>
#include <kernel/network/internet/IP4Interface.h>

class IP4Route {

private:
    IP4Address *netAddress = nullptr;
    IP4Netmask *netMask = nullptr;
    IP4Address *nextHopAddress = nullptr;
    Kernel::IP4Interface *outInterface = nullptr;

public:
    IP4Route(IP4Address *netAddress, IP4Netmask *netMask, IP4Address *nextHop, Kernel::IP4Interface *outInterface);

    IP4Route(IP4Address *netAddress, IP4Netmask *netMask, Kernel::IP4Interface *outInterface);

    uint8_t sendOut(IP4Datagram *datagram);

    [[nodiscard]] Kernel::IP4Interface *getOutInterface() const;

    uint8_t matchingBits(uint8_t *targetBitCount, IP4Address *ip4Address);

    String asString();
};

#endif //HHUOS_IP4ROUTE_H
