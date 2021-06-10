//
// Created by hannes on 17.05.21.
//

#include <kernel/event/network/UDP4ReceiveEvent.h>
#include <kernel/event/network/UDP4SendEvent.h>
#include <kernel/event/network/IP4SendEvent.h>
#include "UDP4Module.h"

namespace Kernel {

    UDP4Module::UDP4Module(Kernel::NetworkEventBus *eventBus) {
        this->eventBus = eventBus;
    }

    void UDP4Module::onEvent(const Kernel::Event &event) {
        if (event.getType() == UDP4SendEvent::TYPE) {
            auto *destinationAddress = ((UDP4SendEvent &) event).getDestinationAddress();
            auto *udp4Datagram = ((UDP4SendEvent &) event).getDatagram();
            //TODO: Add nullcheck for internal data structure
            if(udp4Datagram == nullptr){
                log.error("Outgoing UDP4 datagram was null, ignoring");
                return;
            }
            if(destinationAddress == nullptr){
                log.error("Destination address was null, discarding message");
                delete udp4Datagram;
                return;
            }
            if (udp4Datagram->getLengthInBytes() == 0) {
                log.error("Outgoing datagram was empty, discarding it");
                delete udp4Datagram;
                return;
            }
            eventBus->publish(
                    new IP4SendEvent(
                            new IP4Datagram(destinationAddress, udp4Datagram)
                    )
            );
            //Address has been copied inside constructor, can be deleted now
            delete destinationAddress;
            return;
        }
        if (event.getType() == UDP4ReceiveEvent::TYPE) {
            //auto *udpDatagram = ((UDP4ReceiveEvent &) event).getDatagram();
            return;
        }
    }

}