#include <iostream>
#include <thread>
#include <chrono>
#include <unistd.h>

int secretValue = 123456;

int main() {
    std::cout << "Target PID: " << getpid() << std::endl;
    int* ptr = &secretValue;
    std::cout << ptr << std::endl;
    while (true) {
        std::cout << "Target running... secretValue = " << secretValue << std::endl;
        
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    return 0;
}
