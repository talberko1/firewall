

#include <iostream>
#include "DpdkServer.h"

constexpr auto MBUF_POOL_SIZE = 65535;

constexpr auto DEVICE_ID = 1;

constexpr auto PORT = 3000;

constexpr auto DB_NAME = "rules.db";

int main(int argc, char *argv[]) {
    try {
        std::cout << "Initializing DPDK..." << std::endl;
        DpdkDeviceManager::initDpdk(pcpp::getCoreMaskForAllMachineCores(), MBUF_POOL_SIZE);
        std::cout << "Successfully initialized DPDK!" << std::endl;

        DpdkServer server(DEVICE_ID, DB_NAME);
        server.run();
    }
    catch (DpdkDeviceException &e) {
        std::cout << "DPDK-DEVICE-EXCEPTION: " << e.getMessage() << std::endl;
    }
    catch (std::exception &e) {
        std::cout << "UNHANDLED EXCEPTION CAUGHT" << e.what() << std::endl;
    }
}