//
// Created by tal on 9/28/20.
//

#include "DpdkDeviceList.h"
#include "IPv4Layer.h"
#include "IDpdkEndDevice.h"

#ifndef SERVER_RECEIVERTHREAD_H
#define SERVER_RECEIVERTHREAD_H

class WorkerThread : public pcpp::DpdkWorkerThread {
private:
    pcpp::DpdkDevice *m_Device;
    bool m_Stop;
    uint32_t m_CoreId;
public:
    WorkerThread(pcpp::DpdkDevice *device);

    ~WorkerThread() {}

    bool run(uint32_t coreId) override;

    void stop() override;

    uint32_t getCoreId() const override;
};

#endif //SERVER_RECEIVERTHREAD_H
