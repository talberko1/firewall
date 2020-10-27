//
// Created by tal on 9/28/20.
//

#ifndef SERVER_IENDDEVICE_H
#define SERVER_IENDDEVICE_H

#include "DpdkDevice.h"

class IDpdkEndDevice {
public:
    virtual uint16_t receive(pcpp::MBufRawPacket **packets, uint16_t length, uint16_t queueId) = 0;

    virtual void process(pcpp::Packet packet) = 0;

    virtual uint16_t send(pcpp::MBufRawPacket **packets, uint16_t length, uint16_t queueId) = 0;

    ~IDpdkEndDevice() = default;

};

#endif //SERVER_IENDDEVICE_H
