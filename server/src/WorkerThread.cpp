

#include "WorkerThread.h"
#include <iostream>

WorkerThread::WorkerThread(IDpdkEndDevice *device) :
        m_Device(device), m_Stop(true), m_CoreId(MAX_NUM_OF_CORES - 1) {}


bool WorkerThread::run(uint32_t coreId) {
    try {
        m_CoreId = coreId;
        m_Stop = false;
        pcpp::MBufRawPacket *packets[64] = {};
        while (!m_Stop) {
            uint16_t received = m_Device->receive(packets, 64, 0);
            std::cout << "received: " << received << std::endl;
            if (received) {
                std::cout << received << std::endl;
                m_Device->process(packets, received);
                m_Device->send(packets, received, 0);
            }
        }
    }
    catch (std::exception &e) {
        std::cerr << "ERROR in file: " << __FILE__ << std::endl;
        std::cerr << "in line: " << __LINE__ << std::endl;
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }
    return true;
}

void WorkerThread::stop() {
    m_Stop = true;
}

uint32_t WorkerThread::getCoreId() const {
    return m_CoreId;
}