//
// Created by tal on 9/15/20.
//

#ifndef SERVER_DPDKSERVER_H
#define SERVER_DPDKSERVER_H

#include "DpdkDevice.h"
#include "DpdkDeviceManager.h"
#include "IDpdkEndDevice.h"
#include "WorkerThread.h"
#include "RulesDB.h"
#include "EthLayer.h"
#include "IPv4Layer.h"
#include "TcpLayer.h"
#include "PayloadLayer.h"
#include "PcapFileCreator.h"
#include <iostream>
#include "PcapFileManager.h"
#include "PcapFilter.h"

class DpdkServer : IDpdkEndDevice {
private:
    pcpp::DpdkDevice *m_DpdkDevice;
    RulesDB m_Db;
public:
    DpdkServer(uint32_t DpdkDeviceId, const char *dbName);

    uint16_t receive(pcpp::MBufRawPacket **packets, uint16_t length, uint16_t queueId) override;

    void process(pcpp::MBufRawPacket **packets, uint16_t received) override;

    uint16_t send(pcpp::MBufRawPacket **packets, uint16_t length, uint16_t queueId) override;

    static void createUnfilteredFile(pcpp::Packet &packet);

    void filter(pcpp::Packet &packet);

    void sendFilteredFile(pcpp::Packet &packet);

    void run();

    void shutdown();
};

#endif //SERVER_DPDKSERVER_H
