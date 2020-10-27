//
// Created by tal on 8/22/20.
//

#ifndef CLIENT_DPDKCLIENT_H
#define CLIENT_DPDKCLIENT_H

#include <exception>
#include <iostream>
#include "PlatformSpecificUtils.h"
#include "DpdkDeviceManager.h"
#include "PcapFileManager.h"
#include "WorkerThread.h"
#include "IDpdkEndDevice.h"
#include "IPv4Layer.h"
#include "EthLayer.h"
#include "TcpLayer.h"
#include "PayloadLayer.h"
#include "Layer.h"

class DpdkClient : IDpdkEndDevice {
private:
    pcpp::DpdkDevice *m_RxDevice;
    pcpp::DpdkDevice *m_TxDevice;
    pcpp::IPv4Address m_ServerAddress;
    uint16_t m_Port;
public:
    explicit DpdkClient(int rxDeviceId, int txDeviceId, const char *serverIp, uint16_t port);

    pcpp::MBufRawPacket *decapsulatePacket(pcpp::Packet &packet) override;

    uint16_t receive(pcpp::MBufRawPacket **packets, uint16_t length, uint16_t queueId) override;

    bool process(pcpp::MBufRawPacket* packet) override;

    pcpp::MBufRawPacket *encapsulatePacket(pcpp::MBufRawPacket *packet) override;

    uint16_t send(pcpp::MBufRawPacket **packets, uint16_t length, uint16_t queueId) override;

    void save(pcpp::MBufRawPacket* packet);

    void startCapture(const char *output);

    void stopCapture();

    void send(const char *input);
};


#endif //CLIENT_DPDKCLIENT_H
