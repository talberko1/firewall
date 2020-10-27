//
// Created by tal on 8/22/20.
//

#include "DpdkClient.h"

DpdkClient::DpdkClient(int rxDeviceId, int txDeviceId, const char *serverIp, uint16_t port) : m_RxDevice(
        DpdkDeviceManager::getDevice(rxDeviceId)),
                                                                                              m_TxDevice(
                                                                                                      DpdkDeviceManager::getDevice(
                                                                                                              txDeviceId)),
                                                                                              m_ServerAddress(serverIp),
                                                                                              m_Port(port) {
    DpdkDeviceManager::openMultiQueues(m_RxDevice, 1, 1);
    if (m_RxDevice != m_TxDevice) {
        DpdkDeviceManager::openMultiQueues(m_TxDevice, 1, 1);
    }
}

uint16_t DpdkClient::receive(pcpp::MBufRawPacket **packets, uint16_t length, uint16_t queueId) {
    return m_RxDevice->receivePackets(packets, length, queueId);
}

pcpp::MBufRawPacket *DpdkClient::decapsulatePacket(pcpp::Packet &packet) {
    pcpp::PayloadLayer *payload = packet.getLayerOfType<pcpp::PayloadLayer>();
    return (pcpp::MBufRawPacket *) (payload->getPayload());
}

bool DpdkClient::process(pcpp::MBufRawPacket* packet) {
    pcpp::Packet parsed(packet);
    pcpp::IPv4Layer *ipLayer = parsed.getLayerOfType<pcpp::IPv4Layer>();
    if (ipLayer->getSrcIpAddress() == m_ServerAddress && ipLayer->getProtocol() == pcpp::TCP) {
        pcpp::MBufRawPacket* original = decapsulatePacket(parsed);
        save(original);
    }
    else {
        pcpp::MBufRawPacket* encapsulated = encapsulatePacket(packet);
        std::cout << encapsulated << std::endl;
    }
    return true;
}

pcpp::MBufRawPacket* DpdkClient::encapsulatePacket(pcpp::MBufRawPacket* packet) {
    pcpp::Packet encapsulated;
    pcpp::EthLayer* newEthernetLayer = new pcpp::EthLayer(pcpp::MacAddress(m_RxDevice->getMacAddress()), pcpp::MacAddress(m_TxDevice->getMacAddress()));
    pcpp::TcpLayer* newTcpLayer = new pcpp::TcpLayer(m_Port + 1, m_Port);
    encapsulated.addLayer(newEthernetLayer);
    // add ip layer between tcp & ethernet
    encapsulated.addLayer(newTcpLayer);
    return (pcpp::MBufRawPacket*) encapsulated.getRawPacket();
}

uint16_t DpdkClient::send(pcpp::MBufRawPacket **packets, uint16_t length, uint16_t queueId) {
    return m_TxDevice->sendPackets(packets, length, queueId);
}

void DpdkClient::startCapture(const char *output) {
    std::vector<pcpp::DpdkWorkerThread *> workers;
    workers.push_back(new WorkerThread(this, output));
    DpdkDeviceManager::startDpdkWorkerThreads(workers);
}

void DpdkClient::stopCapture() {
    DpdkDeviceManager::stopDpdkWorkerThreads();
}

void DpdkClient::save(pcpp::MBufRawPacket *packet) {

}


void DpdkClient::send(const char *input) {
    pcpp::IFileReaderDevice *reader(pcpp::IFileReaderDevice::getReader(input));
    PcapFileManager::openPcapReader(reader);
    pcpp::RawPacket pdu;
    pcpp::MBufRawPacket packet;
    while (reader->getNextPacket(pdu)) {
        packet.setRawData((const uint8_t *) &pdu, sizeof(pdu), pdu.getPacketTimeStamp());
        pcpp::Packet parsed(&packet);
        pcpp::IPv4Layer *ipLayer = parsed.getLayerOfType<pcpp::IPv4Layer>();
        ipLayer->setDstIpAddress(m_ServerAddress);
        pcpp::TcpLayer *tcpLayer = parsed.getLayerOfType<pcpp::TcpLayer>();
        tcpLayer->getTcpHeader()->portSrc = m_Port;
    }
    reader->close();
    delete reader;
}
