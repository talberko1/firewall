//
// Created by tal on 9/28/20.
//

#ifndef SERVER_IENDDEVICE_H
#define SERVER_IENDDEVICE_H

#include "DpdkDevice.h"
#include <cstdlib>

class IDpdkEndDevice {
public:

    virtual uint16_t receive(pcpp::MBufRawPacket **packets, uint16_t length, uint16_t queueId) = 0;

    virtual void process(pcpp::MBufRawPacket **packets, uint16_t received) = 0;

    virtual uint16_t send(pcpp::MBufRawPacket **packets, uint16_t length, uint16_t queueId) = 0;

    ~IDpdkEndDevice() = default;
};

#endif //SERVER_IENDDEVICE_H
