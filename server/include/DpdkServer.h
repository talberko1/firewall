//
// Created by tal on 9/15/20.
//

#ifndef SERVER_DPDKSERVER_H
#define SERVER_DPDKSERVER_H

#include "DpdkDevice.h"
#include "DpdkDeviceManager.h"
#include "IDpdkEndDevice.h"
#include "WorkerThread.h"
#include "SqliteDB.h"
#include "EthLayer.h"
#include "IPv4Layer.h"
#include "TcpLayer.h"
#include "PayloadLayer.h"
#include "PcapFileCreator.h"
#include <iostream>

class DpdkServer : IDpdkEndDevice {
private:
    pcpp::DpdkDevice *m_DpdkDevice;
    SqliteDB m_Db;
public:
    DpdkServer(uint32_t DpdkDeviceId, const char *dbName);

    uint16_t receive(pcpp::MBufRawPacket **packets, uint16_t length, uint16_t queueId) override;

    void process(pcpp::MBufRawPacket **packets, uint16_t received) override;

    uint16_t send(pcpp::MBufRawPacket **packets, uint16_t length, uint16_t queueId) override;

    void createFilteredFile(pcpp::Packet &packet);

    static void createUnfilteredFile(pcpp::Packet &packet);

    void sendFilteredFile(pcpp::Packet &packet);

    bool filter(pcpp::Packet &parsedPacket);

    void run();

    void shutdown();
};

#endif //SERVER_DPDKSERVER_H
