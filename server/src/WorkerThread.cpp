

#include "WorkerThread.h"

WorkerThread::WorkerThread(IDpdkEndDevice* device) :
        m_Device(device), m_Stop(true), m_CoreId(MAX_NUM_OF_CORES - 1) {}


bool WorkerThread::run(uint32_t coreId) {
    m_CoreId = coreId;
    m_Stop = false;
    pcpp::MBufRawPacket *packets[MAX_RECEIVE_BURST];
    while (!m_Stop) {
        uint16_t received = m_Device->receive(packets, MAX_RECEIVE_BURST, 0);
        for (int i = 0; i < received; i++) {
            // Actual packet that was captured on client side
            auto payload = (pcpp::MBufRawPacket *) packets[i]->getRawData();
            m_Device->process(payload);
        }
        m_Device->send(packets, received, 0);
    }
    return true;
}

void WorkerThread::stop() {
    m_Stop = true;
}

uint32_t WorkerThread::getCoreId() const {
    return m_CoreId;
}