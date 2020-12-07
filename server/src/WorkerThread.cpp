

#include "WorkerThread.h"
#include <iostream>
#include "PcapFileManager.h"

WorkerThread::WorkerThread(pcpp::DpdkDevice *device) :
        m_Device(device), m_Stop(true), m_CoreId(MAX_NUM_OF_CORES - 1) {}


bool WorkerThread::run(uint32_t coreId) {
    m_CoreId = coreId;
    m_Stop = false;
    pcpp::MBufRawPacket *packets[64] = {};
    while (!m_Stop) {
        uint16_t received = m_Device->receivePackets(packets, 64, 0);
        if (received) {
            m_Device->sendPackets(packets, received, 0);
        }
    }
    std::cout << "finished capturing" << std::endl;
    return true;
}

void WorkerThread::stop() {
    m_Stop = true;
}

uint32_t WorkerThread::getCoreId() const {
    return m_CoreId;
}