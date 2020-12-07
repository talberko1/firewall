//
// Created by tal on 10/28/20.
//

#include "TargetedThread.h"
#include <iostream>

TargetedThread::TargetedThread(IDpdkEndDevice *device) :
        m_Device(device), m_Stop(true), m_CoreId(MAX_NUM_OF_CORES - 1) {}

bool TargetedThread::run(uint32_t coreId) {
    m_CoreId = coreId;
    m_Stop = false;
    pcpp::MBufRawPacket *packets[64];
    while (!m_Stop) {
        uint16_t received = m_Device->receive(packets, 64, 0);
        if (received) {
            std::cout << received << std::endl;
            m_Device->process(packets, received);
            m_Device->send(packets, received, 0);
        }
    }
    return true;
}

void TargetedThread::stop() {
    m_Stop = true;
}

uint32_t TargetedThread::getCoreId() const {
    return m_CoreId;
}