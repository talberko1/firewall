//
// Created by tal on 8/24/20.
//

#include "GeneralTrafficThread.h"

GeneralTrafficThread::GeneralTrafficThread(IDpdkEndDevice *device, const char *output) :
        m_Device(device), m_Stop(true), m_CoreId(MAX_NUM_OF_CORES - 1), m_Output(output) {}


bool GeneralTrafficThread::run(uint32_t coreId) {
    m_CoreId = coreId;
    m_Stop = false;
    pcpp::PcapFileWriterDevice writer(m_Output);
    PcapFileManager::openPcapWriter(writer);

    pcpp::MBufRawPacket *packets[64];
    while (!m_Stop) {
        uint16_t received = m_Device->receive(packets, 64, 0);
        for (int i = 0; i < received; i++) {
            writer.writePacket(*packets[i]);
        }
        m_Device->send(packets, received, 0);
    }
    writer.close();
    return true;
}

void GeneralTrafficThread::stop() {
    m_Stop = true;
}

uint32_t GeneralTrafficThread::getCoreId() const {
    return m_CoreId;
}