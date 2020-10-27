

#include "DpdkServer.h"

DpdkServer::DpdkServer(uint32_t rxDeviceId, uint32_t txDeviceId, uint16_t port, const char *dbName) :
        m_RxDevice(DpdkDeviceManager::getDevice(rxDeviceId)),
        m_TxDevice(DpdkDeviceManager::getDevice(txDeviceId)),
        m_Port(port), m_Db() {
    DpdkDeviceManager::openMultiQueues(m_RxDevice, 1, 1);
    if (m_RxDevice != m_TxDevice) {
        DpdkDeviceManager::openMultiQueues(m_TxDevice, 1, 1);
    }
    m_Db.open(dbName);
}

uint16_t DpdkServer::receive(pcpp::MBufRawPacket **packets, uint16_t length, uint16_t queueId) {
    return m_RxDevice->receivePackets(packets, length, queueId);
}

void DpdkServer::process(pcpp::Packet packet) {

}

uint16_t DpdkServer::send(pcpp::MBufRawPacket **packets, uint16_t length, uint16_t queueId) {
    return m_TxDevice->sendPackets(packets, length, queueId);
}

void DpdkServer::run() {
    std::vector<pcpp::DpdkWorkerThread *> workers;
    workers.push_back(new WorkerThread(this));
    DpdkDeviceManager::startDpdkWorkerThreads(workers);
}

void DpdkServer::shutdown() {
    DpdkDeviceManager::stopDpdkWorkerThreads();
    m_Db.close();
}

