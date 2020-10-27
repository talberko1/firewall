#include <iostream>
#include "DpdkClient.h"

constexpr auto RX_DEVICE_ID = 0;
constexpr auto TX_DEVICE_ID = 0;
constexpr auto SLEEP_DURATION = 20;
constexpr auto MBUF_POOL_SIZE = 65535;
constexpr auto OUTPUT = "output.pcap";
constexpr auto SERVER_IP = "127.0.0.1";
constexpr auto SERVER_PORT = 3000;

int main(int argc, char *argv[]) {
    try {
        std::cout << "Initializing DPDK" << std::endl;
        DpdkDeviceManager::initDpdk(pcpp::getCoreMaskForAllMachineCores(), MBUF_POOL_SIZE);
        std::cout << "Successfully initialized DPDK" << std::endl;

        std::cout << "Opening DPDK device" << std::endl;
        DpdkClient client(RX_DEVICE_ID, TX_DEVICE_ID, SERVER_IP, SERVER_PORT);
        std::cout << "Successfully opened DPDK device" << std::endl;

        std::cout << "Capturing traffic through DPDK device" << std::endl;
        client.startCapture(OUTPUT);
        PCAP_SLEEP(SLEEP_DURATION);
        client.stopCapture();
        client.send(OUTPUT);
    }
    catch(DpdkDeviceException& e) {
        std::cout << "DPDK-DEVICE-EXCEPTION: " << e.getMessage() << std::endl;
    }
    catch(std::exception& e) {
        std::cout << "UNHANDLED EXCEPTION CAUGHT" << e.what() << std::endl;
    }
}