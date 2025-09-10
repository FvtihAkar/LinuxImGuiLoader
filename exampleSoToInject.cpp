#include <cstdint>
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>

__attribute__((constructor))
void on_load() {
    pid_t pid = getpid();
    std::cout << "[SO] Loaded into PID: " << pid << std::endl;

    uintptr_t offset = 0x50; // scanmem ile bulduğun offset

    // target binary'nin base adresini bul
    uintptr_t base = 0;
    std::ifstream maps("/proc/self/maps");
    std::string line;
    while (std::getline(maps, line)) {
        if (line.find("target") != std::string::npos && line.find("rw-p") != std::string::npos) {
            base = std::stoull(line.substr(0, line.find('-')), nullptr, 16);
            break;
        }
    }

    if (!base) {
        std::cerr << "[SO] Cannot find base address!" << std::endl;
        return;
    }

    uintptr_t addr = base + offset;
    std::cout << "[SO] base = " << std::hex << base << ", addr = " << addr << std::endl;

    // Direkt pointer
    int* ptr = reinterpret_cast<int*>(addr);

    int value = *ptr;
    *ptr = 1111;
    std::cout << "[SO] Read secretValue via pointer: " << std::dec << value << std::endl;
}
