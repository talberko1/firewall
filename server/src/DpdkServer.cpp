

#include "DpdkServer.h"
#include "PcapFileCreator.h"

DpdkServer::DpdkServer(uint32_t DpdkDeviceId, const char *dbName) :
        m_DpdkDevice(DpdkDeviceManager::getDevice(DpdkDeviceId)), m_Db() {
    DpdkDeviceManager::openMultiQueues(m_DpdkDevice, 1, 1);
    m_Db.open(dbName);
    std::cout << "Server MAC address: " << m_DpdkDevice->getMacAddress().toString() << std::endl;
}

uint16_t DpdkServer::receive(pcpp::MBufRawPacket **packets, uint16_t length, uint16_t queueId) {
    return m_DpdkDevice->receivePackets(packets, length, queueId);
}

void DpdkServer::process(pcpp::MBufRawPacket **packets, uint16_t received) {
    try {
        int i = 0;
        bool receivedRequest = false;
        for (; i < received && !receivedRequest; i++) {
            pcpp::Packet parsedPacket(packets[i]);
            pcpp::EthLayer *ethernetLayer = parsedPacket.getLayerOfType<pcpp::EthLayer>();
            receivedRequest = ethernetLayer->getDestMac() == m_DpdkDevice->getMacAddress();
        }
        if (receivedRequest) {
            std::cout << "SOMEONE SENT REQUEST HERE" << std::endl;
            pcpp::Packet parsedPacket(packets[i - 1]);
            createUnfilteredFile(parsedPacket);
            //reader->addFilter... or just filter a packet one by one
            sendFilteredFile(parsedPacket);
        }
    }
    catch(std::exception& e) {
        std::cerr << "ERROR in file: " << __FILE__ << std::endl;
        std::cerr << "in line: " << __LINE__ << std::endl;
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }
}

void DpdkServer::createUnfilteredFile(pcpp::Packet &packet) {
    pcpp::EthLayer *requestEthernetLayer = packet.getLayerOfType<pcpp::EthLayer>();
    pcpp::PayloadLayer *requestPayloadLayer = packet.getLayerOfType<pcpp::PayloadLayer>();
    uint8_t *requestData = requestPayloadLayer->getPayload();
    size_t requestLength = requestPayloadLayer->getPayloadLen();
    std::string unfiltered = requestEthernetLayer->getSourceMac().toString() + ".pcap";
    PcapFileCreator::createFileFromBytes(unfiltered.c_str(), requestData, requestLength);
}

void DpdkServer::createFilteredFile(pcpp::Packet &packet) {

}

void DpdkServer::sendFilteredFile(pcpp::Packet &packet) {
    pcpp::EthLayer *requestEthernetLayer = packet.getLayerOfType<pcpp::EthLayer>();
    std::string filtered = requestEthernetLayer->getSourceMac().toString() + "-filtered.pcap";
    const uint8_t *responseData = PcapFileCreator::createByteStreamFromFile(filtered.c_str());
    long responseLength = PcapFileCreator::getFileSize(filtered.c_str());
    pcpp::Packet response;
    pcpp::EthLayer *responseEthernetLayer = new pcpp::EthLayer(m_DpdkDevice->getMacAddress(), requestEthernetLayer->getSourceMac());
    pcpp::PayloadLayer *responsePayloadLayer = new pcpp::PayloadLayer(responseData, responseLength, false);
    response.addLayer(responseEthernetLayer);
    response.addLayer(responsePayloadLayer);
    m_DpdkDevice->sendPacket(response);
}

uint16_t DpdkServer::send(pcpp::MBufRawPacket **packets, uint16_t length, uint16_t queueId) {
    return m_DpdkDevice->sendPackets(packets, length, queueId);
}

void DpdkServer::run() {
    std::vector<pcpp::DpdkWorkerThread *> workers;
    workers.push_back(new WorkerThread(this));
    DpdkDeviceManager::startDpdkWorkerThreads(workers);
}

void DpdkServer::shutdown() {
    DpdkDeviceManager::stopDpdkWorkerThreads();
    m_DpdkDevice->close();
    m_Db.close();
}

