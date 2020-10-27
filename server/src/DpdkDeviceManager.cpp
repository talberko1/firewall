//
// Created by tal on 8/29/20.
//

#include "DpdkDeviceManager.h"

void DpdkDeviceManager::initDpdk(pcpp::CoreMask coreMask, int mbufPoolSize) {
    pcpp::DpdkDeviceList::initDpdk(coreMask, mbufPoolSize);
}

pcpp::DpdkDevice *DpdkDeviceManager::getDevice(int deviceId) {
    pcpp::DpdkDevice *device = pcpp::DpdkDeviceList::getInstance().getDeviceByPort((deviceId));
    if (!device) {
        throw DpdkDeviceException("Cannot find a device with the given port");
    }
    return device;
}

void DpdkDeviceManager::openMultiQueues(pcpp::DpdkDevice *device, int rx, int tx) {
    if (!device->openMultiQueues(rx, tx)) {
        throw DpdkDeviceException("Couldn't open the given device");
    }
}

void DpdkDeviceManager::startDpdkWorkerThreads(std::vector<pcpp::DpdkWorkerThread *> &workers) {
    uint32_t workersCoreMask = 0;
    for (size_t i = 1; i <= workers.size(); i++) {
        workersCoreMask |= (1 << (i + 1));
    }
    if (!pcpp::DpdkDeviceList::getInstance().startDpdkWorkerThreads(workersCoreMask, workers)) {
        throw DpdkDeviceException("Couldn't start worker threads");
    }
}

void DpdkDeviceManager::stopDpdkWorkerThreads() {
    pcpp::DpdkDeviceList::getInstance().stopDpdkWorkerThreads();
}