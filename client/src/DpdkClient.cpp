//
// Created by tal on 8/22/20.
//

#include "DpdkClient.h"

DpdkClient::DpdkClient(int dpdkDeviceId, const char *serverMacAddress) :
        m_DpdkDevice(DpdkDeviceManager::getDevice(dpdkDeviceId)), m_ServerMacAddress(serverMacAddress) {
    DpdkDeviceManager::openMultiQueues(m_DpdkDevice, 1, 1);
    std::cout << "Client MAC address: " << m_DpdkDevice->getMacAddress().toString() << std::endl;
}

uint16_t DpdkClient::receive(pcpp::MBufRawPacket **packets, uint16_t length, uint16_t queueId) {
    return m_DpdkDevice->receivePackets(packets, length, queueId);
}

void DpdkClient::process(pcpp::MBufRawPacket **packets, uint16_t received) {
    int i = 0;
    bool receivedResponse = false;
    for (; i < received && !receivedResponse; i++) {
        pcpp::Packet parsedPacket(packets[i]);
        pcpp::EthLayer *ethernetLayer = parsedPacket.getLayerOfType<pcpp::EthLayer>();
        receivedResponse = ethernetLayer->getSourceMac() == m_ServerMacAddress && ethernetLayer->getDestMac() == m_DpdkDevice->getMacAddress();
    }
    if (receivedResponse) {
        pcpp::Packet parsedPacket(packets[i - 1]);
        pcpp::PayloadLayer *payloadLayer = parsedPacket.getLayerOfType<pcpp::PayloadLayer>();
        uint8_t *data = payloadLayer->getPayload();
        size_t length = payloadLayer->getPayloadLen();
        PcapFileCreator::createFileFromBytes("filtered.pcap", data, length);
        stopCapture();
    }
}

uint16_t DpdkClient::send(pcpp::MBufRawPacket **packets, uint16_t length, uint16_t queueId) {
    return m_DpdkDevice->sendPackets(packets, length, queueId);
}

void DpdkClient::startGeneralThread(const char *output) {
    std::vector<pcpp::DpdkWorkerThread *> workers;
    workers.push_back(new GeneralTrafficThread(this, output));
    DpdkDeviceManager::startDpdkWorkerThreads(workers);
}

void DpdkClient::startTargetedThread(const char *output) {
    std::vector<pcpp::DpdkWorkerThread *> workers;
    workers.push_back(new TargetedThread(this, output));
    DpdkDeviceManager::startDpdkWorkerThreads(workers);
}

void DpdkClient::stopCapture() {
    DpdkDeviceManager::stopDpdkWorkerThreads();
}

void DpdkClient::sendPcapFile(const char *input) {

}
