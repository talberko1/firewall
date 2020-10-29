#include <iostream>
#include "DpdkClient.h"

constexpr auto DEVICE_ID = 1;
constexpr auto SLEEP_DURATION = 5;
constexpr auto MBUF_POOL_SIZE = 65535;
constexpr auto OUTPUT = "output.pcap";
constexpr auto SERVER_MAC_ADDRESS = "08:00:27:93:e1:6f";

int main(int argc, char *argv[]) {
    try {
        std::cout << "Initializing DPDK" << std::endl;
        DpdkDeviceManager::initDpdk(pcpp::getCoreMaskForAllMachineCores(), MBUF_POOL_SIZE);
        std::cout << "Successfully initialized DPDK" << std::endl;

        std::cout << "Opening DPDK device" << std::endl;
        DpdkClient client(DEVICE_ID, SERVER_MAC_ADDRESS);
        std::cout << "Successfully opened DPDK device" << std::endl;

        std::cout << "Capturing traffic through DPDK device" << std::endl;
        client.startGeneralThread(OUTPUT);
        PCAP_SLEEP(SLEEP_DURATION);
        DpdkClient::stopCapture();
        //client.send(OUTPUT);
        //client.startTargetedThread();
    }
    catch (DpdkDeviceException &e) {
        std::cout << "DPDK-DEVICE-EXCEPTION: " << e.getMessage() << std::endl;
    }
    catch (std::exception &e) {
        std::cout << "UNHANDLED EXCEPTION CAUGHT" << e.what() << std::endl;
    }
}