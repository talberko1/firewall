//
// Created by tal on 9/28/20.
//

#ifndef CLIENT_IENDDEVICE_H
#define CLIENT_IENDDEVICE_H
#include <cstdlib>
#include "DpdkDevice.h"

class IDpdkEndDevice {
public:
    virtual pcpp::MBufRawPacket *decapsulatePacket(pcpp::Packet &packet) = 0;

    virtual uint16_t receive(pcpp::MBufRawPacket **packets, uint16_t length, uint16_t queueId) = 0;

    virtual bool process(pcpp::MBufRawPacket* packet) = 0;

    virtual pcpp::MBufRawPacket *encapsulatePacket(pcpp::MBufRawPacket *packet) = 0;

    virtual uint16_t send(pcpp::MBufRawPacket **packets, uint16_t length, uint16_t queueId) = 0;

    ~IDpdkEndDevice() = default;
};

#endif //SERVER_IENDDEVICE_H
