

#include "DpdkServer.h"
#include "PcapFileCreator.h"

DpdkServer::DpdkServer(uint32_t DpdkDeviceId, const char *dbName) :
        m_DpdkDevice(DpdkDeviceManager::getDevice(DpdkDeviceId)), m_Db(dbName) {
    DpdkDeviceManager::openMultiQueues(m_DpdkDevice, 1, 1);
    std::cout << "Server MAC address: " << m_DpdkDevice->getMacAddress().toString() << std::endl;
}

uint16_t DpdkServer::receive(pcpp::MBufRawPacket **packets, uint16_t length, uint16_t queueId) {
    return m_DpdkDevice->receivePackets(packets, length, queueId);
}

void DpdkServer::process(pcpp::MBufRawPacket **packets, uint16_t received) {
    int i = 0;
    bool receivedRequest = false;
    for (; i < received && !receivedRequest; i++) {
        pcpp::Packet parsedPacket(packets[i]);
        pcpp::EthLayer *ethernetLayer = parsedPacket.getLayerOfType<pcpp::EthLayer>();
        receivedRequest = ethernetLayer->getDestMac().toString() == m_DpdkDevice->getMacAddress().toString();
    }
    if (receivedRequest) {
        std::cout << "RECEIVED CLIENT REQUEST" << std::endl;
        pcpp::Packet parsedPacket(packets[i - 1]);
        createUnfilteredFile(parsedPacket);
        filter(parsedPacket);
        sendFilteredFile(parsedPacket);
    }
}

void DpdkServer::createUnfilteredFile(pcpp::Packet &packet) {
    pcpp::EthLayer *requestEthernetLayer = packet.getLayerOfType<pcpp::EthLayer>();
    pcpp::PayloadLayer *requestPayloadLayer = packet.getLayerOfType<pcpp::PayloadLayer>();
    uint8_t *requestData = requestPayloadLayer->getPayload();
    size_t requestLength = requestPayloadLayer->getPayloadLen();
    std::string unfiltered = requestEthernetLayer->getSourceMac().toString() + ".pcap";
    PcapFileCreator::createFileFromBytes(unfiltered.c_str(), (char*)requestData, requestLength);
}

void DpdkServer::filter(pcpp::Packet &packet) {
    pcpp::EthLayer *requestEthernetLayer = packet.getLayerOfType<pcpp::EthLayer>();
    std::string unfiltered = requestEthernetLayer->getSourceMac().toString() + ".pcap";
    std::string filtered = requestEthernetLayer->getSourceMac().toString() + "-filtered.pcap";

    pcpp::IFileReaderDevice *reader = pcpp::IFileReaderDevice::getReader(unfiltered.c_str());
    pcpp::RawPacket raw;
    std::vector<Rule*> rules = m_Db.getRules();
    std::vector<pcpp::RawPacket> buffer;
    for (Rule *rule : rules) {
        PcapFileManager::openPcapReader(reader);
        reader->setFilter(*rule->m_Filter);
        while (reader->getNextPacket(raw)) {
            if (rule->m_Action == std::string("FORWARD")) {
                pcpp::Packet parsed(&raw);
                std::cout << parsed.toString() << std::endl;
                buffer.push_back(raw);
            }
        }
        reader->close();
        pcpp::PcapFileWriterDevice writer(filtered.c_str());
        PcapFileManager::openPcapWriter(writer);
        for (auto &rawPacket : buffer) {
            writer.writePacket(rawPacket);
        }
        writer.close();
    }
}

void DpdkServer::sendFilteredFile(pcpp::Packet &packet) {
    pcpp::EthLayer *requestEthernetLayer = packet.getLayerOfType<pcpp::EthLayer>();
    std::string filtered = requestEthernetLayer->getSourceMac().toString() + "-filtered.pcap";
    const char *responseData = PcapFileCreator::createByteStreamFromFile(filtered.c_str(), PcapFileCreator::getFileSize(filtered.c_str()));
    long responseLength = PcapFileCreator::getFileSize(filtered.c_str());
    pcpp::Packet response;
    pcpp::EthLayer *responseEthernetLayer = new pcpp::EthLayer(m_DpdkDevice->getMacAddress(),
                                                               requestEthernetLayer->getSourceMac());
    pcpp::PayloadLayer *responsePayloadLayer = new pcpp::PayloadLayer((uint8_t*)responseData, responseLength, false);
    response.addLayer(responseEthernetLayer);
    response.addLayer(responsePayloadLayer);
    response.computeCalculateFields();
    m_DpdkDevice->sendPacket(response);
}

uint16_t DpdkServer::send(pcpp::MBufRawPacket **packets, uint16_t length, uint16_t queueId) {
    return m_DpdkDevice->sendPackets(packets, length, queueId);
}

void DpdkServer::run() {
    std::cout << "Capturing on pci: " << m_DpdkDevice->getPciAddress() << std::endl;
//    std::vector<pcpp::DpdkWorkerThread *> workers;
//    workers.push_back(new WorkerThread(m_DpdkDevice));
//    DpdkDeviceManager::startDpdkWorkerThreads(workers);

    pcpp::MBufRawPacket *packets[64] = {};
    while (true) {
        uint16_t received = m_DpdkDevice->receivePackets(packets, 64, 0);
        if (received) {
            process(packets, received);
            m_DpdkDevice->sendPackets(packets, received, 0);
        }
    }
}

void DpdkServer::shutdown() {
    //DpdkDeviceManager::stopDpdkWorkerThreads();
    m_DpdkDevice->close();
    m_Db.close();
}

