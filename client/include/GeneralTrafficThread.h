//
// Created by tal on 8/24/20.
//

#ifndef CLIENT_GENERALTRAFFICTHREAD_H
#define CLIENT_GENERALTRAFFICTHREAD_H

#include "DpdkDeviceList.h"
#include "PcapFileManager.h"
#include "IDpdkEndDevice.h"

class GeneralTrafficThread : public pcpp::DpdkWorkerThread {
private:
    IDpdkEndDevice *m_Device;
    bool m_Stop;
    uint32_t m_CoreId;

    const char *m_Output;
public:
    GeneralTrafficThread(IDpdkEndDevice *device, const char *output);

    ~GeneralTrafficThread() {}

    bool run(uint32_t coreId) override;

    void stop() override;

    uint32_t getCoreId() const override;
};

#endif //CLIENT_GENERALTRAFFICTHREAD_H
