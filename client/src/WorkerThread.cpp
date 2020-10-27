//
// Created by tal on 8/24/20.
//

#include "WorkerThread.h"

WorkerThread::WorkerThread(IDpdkEndDevice *device, const char *output) :
        m_Device(device), m_Stop(true), m_CoreId(MAX_NUM_OF_CORES - 1), m_Output(output) {}


bool WorkerThread::run(uint32_t coreId) {
    m_CoreId = coreId;
    m_Stop = false;
    pcpp::PcapFileWriterDevice writer(m_Output);
    PcapFileManager::openPcapWriter(writer);
    pcpp::MBufRawPacket *packets[MAX_RECEIVE_BURST];
    while (!m_Stop) {
        uint16_t received = m_Device->receive(packets, MAX_RECEIVE_BURST, 0);
        for (int i = 0; i < received; i++) {
            m_Device->process(packets[i]);
            writer.writePacket(*packets[i]);
            delete packets[i];
        }
    }
    writer.close();
    return true;
}

void WorkerThread::stop() {
    m_Stop = true;
}

uint32_t WorkerThread::getCoreId() const {
    return m_CoreId;
}