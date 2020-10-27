//
// Created by tal on 8/24/20.
//

#ifndef CLIENT_WORKERTHREAD_H
#define CLIENT_WORKERTHREAD_H

#include "DpdkDeviceList.h"
#include "PcapFileManager.h"
#include "IDpdkEndDevice.h"

constexpr auto MAX_RECEIVE_BURST = 64;

class WorkerThread : public pcpp::DpdkWorkerThread {
private:
    IDpdkEndDevice *m_Device;
    bool m_Stop;
    uint32_t m_CoreId;

    const char *m_Output;
public:
    WorkerThread(IDpdkEndDevice *device, const char *output);

    ~WorkerThread() {}

    bool run(uint32_t coreId) override;

    void stop() override;

    uint32_t getCoreId() const override;
};

#endif //CLIENT_WORKERTHREAD_H
