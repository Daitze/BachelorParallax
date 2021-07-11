//
// Created by hannes on 15.06.21.
//

#include <kernel/network/NetworkDefinitions.h>
#include "EthernetHeader.h"

EthernetHeader::EthernetHeader(EthernetAddress *destinationAddress, EthernetDataPart *dataPart) {
    this->destinationAddress = destinationAddress;
    this->etherType = dataPart->getEtherType();
}

EthernetHeader::~EthernetHeader() {
    delete destinationAddress;
    delete sourceAddress;
}

EthernetDataPart::EtherType EthernetHeader::getEtherType() const {
    return etherType;
}

uint16_t EthernetHeader::length() {
    return 2 * ETH_ADDRESS_LENGTH + sizeof(uint16_t);
}

uint16_t EthernetHeader::maximumFrameLength() {
    return (uint16_t) (length() + ETHERNET_MTU);
}

uint8_t EthernetHeader::setSourceAddress(EthernetAddress *address) {
    if (address == nullptr) {
        return 1;
    }
    this->sourceAddress = address;
    return 0;
}

uint8_t EthernetHeader::copyTo(Kernel::NetworkByteBlock *output) {
    if (output == nullptr) {
        return 1;
    }
    uint8_t errors = 0;

    uint8_t addressBytes[ETH_ADDRESS_LENGTH];
    destinationAddress->copyTo(addressBytes);
    errors += output->appendStraightFrom(addressBytes, ETH_ADDRESS_LENGTH);

    if (errors) {
        return errors;
    }

    sourceAddress->copyTo(addressBytes);
    errors += output->appendStraightFrom(addressBytes, ETH_ADDRESS_LENGTH);

    if (errors) {
        return errors;
    }

    errors += output->appendTwoBytesSwapped((uint16_t) etherType);
    return errors;
}

uint8_t EthernetHeader::parse(Kernel::NetworkByteBlock *input) {
    if (input == nullptr || input->bytesRemaining() < length()) {
        return 1;
    }

    uint8_t errors = 0;
    uint8_t addressBytes[ETH_ADDRESS_LENGTH];

    errors += input->readStraightTo(addressBytes, ETH_ADDRESS_LENGTH);
    destinationAddress = new EthernetAddress(addressBytes);

    if (errors) {
        return errors;
    }

    errors += input->readStraightTo(addressBytes, ETH_ADDRESS_LENGTH);
    sourceAddress = new EthernetAddress(addressBytes);

    if (errors) {
        return errors;
    }

    uint16_t typeValue = 0;
    errors += input->readTwoBytesSwappedTo(&typeValue);
    etherType = EthernetDataPart::parseIntAsEtherType(typeValue);

    return errors;
}

bool EthernetHeader::destinationIs(EthernetAddress *otherAddress) {
    if (otherAddress == nullptr || destinationAddress == nullptr) {
        return false;
    }
    return destinationAddress->equals(otherAddress);
}