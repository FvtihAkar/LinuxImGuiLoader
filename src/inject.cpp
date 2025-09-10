// gdb_injector.cpp
// Derleme: g++ -O2 -std=c++17 gdb_injector.cpp -o gdb_injector
// Kullanım: sudo ./gdb_injector <process_name> /full/path/to/lib.so

#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <unistd.h>
#include <algorithm>
#include <sys/types.h>
#include <dirent.h>

class GDBInjector {
public:
    // Constructor: process name ve .so path
    GDBInjector(std::string processName, std::string soPath)
        : processName_(std::move(processName)), soPath_(std::move(soPath)) {}

    // Injection fonksiyonu
    bool inject() {
        auto pid = findProcessPid();
        if (pid == -1) {
            std::cerr << "[!] Process not found: " << processName_ << "\n";
            return false;
        }

        std::cout << "[*] Found PID: " << pid << "\n";

        // Escape quotes for GDB command
        std::string escSoPath;
        for (char c : soPath_) {
            if (c == '"' || c == '\\') escSoPath.push_back('\\');
            escSoPath.push_back(c);
        }

        // GDB komutunu oluştur
        std::ostringstream gdbCmd;
        gdbCmd << "gdb -q --batch "
               << "-ex \"attach " << pid << "\" "
               << "-ex \"call (void*) dlopen(\\\"" << escSoPath << "\\\", 2)\" "
               << "-ex \"detach\" "
               << "-ex \"quit\"";

        std::cout << "[*] Running GDB command: " << gdbCmd.str() << "\n";

        int ret = std::system(gdbCmd.str().c_str());
        if (ret != 0) {
            std::cerr << "[!] GDB command failed with code: " << ret << "\n";
            return false;
        }

        std::cout << "[+] Injection complete.\n";
        return true;
    }

private:
    std::string processName_;
    std::string soPath_;

    // process name ile PID bulma
    pid_t findProcessPid() {
        DIR* procDir = opendir("/proc");
        if (!procDir) {
            perror("opendir");
            return -1;
        }

        struct dirent* entry;
        while ((entry = readdir(procDir)) != nullptr) {
            if (!std::all_of(entry->d_name, entry->d_name + strlen(entry->d_name), ::isdigit))
                continue;

            pid_t pid = std::stoi(entry->d_name);
            std::string cmdPath = "/proc/" + std::to_string(pid) + "/comm";
            std::ifstream cmdFile(cmdPath);
            if (!cmdFile.is_open()) continue;

            std::string cmdName;
            std::getline(cmdFile, cmdName);
            cmdFile.close();

            if (cmdName == processName_) {
                closedir(procDir);
                return pid;
            }
        }
        closedir(procDir);
        return -1;
    }
};