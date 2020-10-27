//
// Created by tal on 8/29/20.
//

#ifndef CLIENT_DPDKDEVICEMANAGER_H
#define CLIENT_DPDKDEVICEMANAGER_H

#include <string>
#include <exception>

#include "DpdkDeviceList.h"

class DpdkDeviceException : public std::exception {
private:
    const char *m_Message;
public:
    explicit DpdkDeviceException(const char *message) : m_Message(message) {}

    const char *getMessage() {
        return m_Message;
    }
};

class DpdkDeviceManager {
public:
    static void initDpdk(pcpp::CoreMask coreMask, int mbufPoolSize);

    static pcpp::DpdkDevice *getDevice(int deviceId);

    static void openMultiQueues(pcpp::DpdkDevice *device, int rx, int tx);

    static void startDpdkWorkerThreads(std::vector<pcpp::DpdkWorkerThread *> &workers);

    static void stopDpdkWorkerThreads();
};

#endif //CLIENT_DPDKDEVICEMANAGER_H
