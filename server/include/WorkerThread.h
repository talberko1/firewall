//
// Created by tal on 9/28/20.
//

#include "DpdkDeviceList.h"
#include "IPv4Layer.h"
#include "IDpdkEndDevice.h"

#ifndef SERVER_RECEIVERTHREAD_H
#define SERVER_RECEIVERTHREAD_H
constexpr auto MAX_RECEIVE_BURST = 64;

class WorkerThread : public pcpp::DpdkWorkerThread {
private:
    IDpdkEndDevice* m_Device;
    bool m_Stop;
    uint32_t m_CoreId;
public:
    WorkerThread(IDpdkEndDevice* device);

    ~WorkerThread() {}

    bool run(uint32_t coreId) override;

    void stop() override;

    uint32_t getCoreId() const override;
};
#endif //SERVER_RECEIVERTHREAD_H
