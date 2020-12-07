//
// Created by tal on 9/28/20.
//

#ifndef SERVER_IENDDEVICE_H
#define SERVER_IENDDEVICE_H

#include "DpdkDevice.h"
#include "DpdkDeviceManager.h"

class IDpdkEndDevice {
//protected:
//    pcpp::DpdkDevice* m_RxDevice;
//    pcpp::DpdkDevice* m_TxDevice;
public:
//    IDpdkEndDevice(uint32_t dpdkDeviceId);
//    IDpdkEndDevice(uint32_t rxDpdkDeviceId, uint32_t txDpdkDeviceId);
    virtual uint16_t receive(pcpp::MBufRawPacket **packets, uint16_t length, uint16_t queueId) = 0;

    virtual void process(pcpp::MBufRawPacket **packets, uint16_t received) = 0;

    virtual uint16_t send(pcpp::MBufRawPacket **packets, uint16_t length, uint16_t queueId) = 0;

    ~IDpdkEndDevice() = default;
};

#endif //SERVER_IENDDEVICE_H
