

#include <iostream>
#include "DpdkServer.h"
#include "mongoc.h"

constexpr uint32_t MBUF_POOL_SIZE = 16*1024 - 1;

constexpr auto DEVICE_ID = 0;

constexpr auto DB_NAME = "rules.db";

int main(int argc, char *argv[]) {
    try {
        std::cout << "Initializing DPDK..." << std::endl;
//        DpdkDeviceManager::initDpdk(pcpp::getCoreMaskForAllMachineCores(), MBUF_POOL_SIZE);
        std::cout << "Successfully initialized DPDK!" << std::endl;
        std::cout << "Opening DPDK device" << std::endl;
//        DpdkServer server(DEVICE_ID, DB_NAME);
        std::cout << "Successfully opened DPDK device" << std::endl;
//        server.run();
    }
    catch (DpdkDeviceException &e) {
        std::cout << "DPDK-DEVICE-EXCEPTION: " << e.what() << std::endl;
    }
    catch(SqliteException &e) {
        std::cout << "SQLITE3-EXCEPTION: " << e.what() << std::endl;
    }
    catch (std::exception &e) {
        std::cout << "UNHANDLED EXCEPTION CAUGHT: " << e.what() << std::endl;
    }
}