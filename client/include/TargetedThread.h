//
// Created by tal on 10/28/20.
//

#ifndef CLIENT_TARGETEDTHREAD_H
#define CLIENT_TARGETEDTHREAD_H

#include "DpdkDeviceList.h"
#include "PcapFileManager.h"
#include "IDpdkEndDevice.h"
#include "EthLayer.h"

class TargetedThread : public pcpp::DpdkWorkerThread {
private:
    IDpdkEndDevice *m_Device;
    bool m_Stop;
    uint32_t m_CoreId;

    const char *m_Output;
public:
    TargetedThread(IDpdkEndDevice *device);

    ~TargetedThread() {}

    bool run(uint32_t coreId) override;

    void stop() override;

    uint32_t getCoreId() const override;
};

#endif //CLIENT_TARGETEDTHREAD_H
