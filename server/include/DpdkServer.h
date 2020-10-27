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

class DpdkServer : IDpdkEndDevice {
private:
    pcpp::DpdkDevice *m_RxDevice;
    pcpp::DpdkDevice *m_TxDevice;
    uint16_t m_Port;
    SqliteDB m_Db;
public:
    DpdkServer(uint32_t rxDeviceId, uint32_t txDeviceId, uint16_t port, const char *dbName);

    uint16_t receive(pcpp::MBufRawPacket **packets, uint16_t length, uint16_t queueId) override;

    void process(pcpp::Packet packet) override;

    uint16_t send(pcpp::MBufRawPacket **packets, uint16_t length, uint16_t queueId) override;

    void run();

    void shutdown();
};

#endif //SERVER_DPDKSERVER_H
