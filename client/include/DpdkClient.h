//
// Created by tal on 8/22/20.
//

#ifndef CLIENT_DPDKCLIENT_H
#define CLIENT_DPDKCLIENT_H

#include <exception>
#include "DpdkDeviceManager.h"
#include "PcapFileManager.h"
#include "GeneralTrafficThread.h"
#include "TargetedThread.h"
#include "IDpdkEndDevice.h"
#include "IPv4Layer.h"
#include "EthLayer.h"
#include "TcpLayer.h"
#include "PayloadLayer.h"
#include "PcapFileCreator.h"
#include <iostream>

class DpdkClient : IDpdkEndDevice {
private:
    pcpp::DpdkDevice *m_DpdkDevice;
    pcpp::MacAddress m_ServerMacAddress;
public:
    explicit DpdkClient(int dpdkDeviceId, const char *serverMacAddress);

    uint16_t receive(pcpp::MBufRawPacket **packets, uint16_t length, uint16_t queueId) override;

    void process(pcpp::MBufRawPacket **packets, uint16_t received) override;

    uint16_t send(pcpp::MBufRawPacket **packets, uint16_t length, uint16_t queueId) override;

    void startGeneralThread(const char *output);

    void startTargetedThread();

    static void stopCapture();

    void sendPcapFile(const char *input);
};


#endif //CLIENT_DPDKCLIENT_H
