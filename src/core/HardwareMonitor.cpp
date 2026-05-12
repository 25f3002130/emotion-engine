#include "core/HardwareMonitor.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>
#include <QString>

#ifdef _WIN32
#include <windows.h>
#include <intrin.h>
#elif __APPLE__
#include <sys/sysctl.h>
#include <sys/types.h>
#else
#include <unistd.h>
#include <sys/sysinfo.h>
#endif

namespace emotion {

std::string exec_cmd(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
#ifdef _WIN32
    std::unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(cmd, "r"), _pclose);
#else
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
#endif
    if (!pipe) return "Unknown";
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

HardwareSpecs HardwareMonitor::scan() {
    HardwareSpecs specs;
    specs.os_version = "Unknown OS";
    specs.cpu_model = "Unknown CPU";
    specs.total_ram_mb = 0;
    specs.gpu_model = "Integrated/Unknown";
    specs.training_score = 0.5f;

#ifdef _WIN32
    // Windows Detection
    specs.os_version = "Windows (Modern)";
    
    MEMORYSTATUSEX status;
    status.dwLength = sizeof(status);
    if (GlobalMemoryStatusEx(&status)) {
        specs.total_ram_mb = status.ullTotalPhys / (1024 * 1024);
    }

    // Basic CPU via registry or wmic
    specs.cpu_model = exec_cmd("wmic cpu get name /format:list");
    specs.gpu_model = exec_cmd("wmic path win32_VideoController get name /format:list");

#elif __APPLE__
    // macOS Detection
    specs.os_version = "macOS (Darwin)";
    
    int64_t mem;
    size_t len = sizeof(mem);
    sysctlbyname("hw.memsize", &mem, &len, NULL, 0);
    specs.total_ram_mb = mem / (1024 * 1024);

    char cpu_brand[256];
    len = sizeof(cpu_brand);
    sysctlbyname("machdep.cpu.brand_string", &cpu_brand, &len, NULL, 0);
    specs.cpu_model = cpu_brand;
    specs.gpu_model = "Apple Silicon / Metal Core";

#else
    // Linux Detection (Current)
    std::ifstream os_file("/etc/os-release");
    std::string line;
    while (std::getline(os_file, line)) {
        if (line.find("PRETTY_NAME=") != std::string::npos) {
            specs.os_version = line.substr(13, line.length() - 14);
            break;
        }
    }

    struct sysinfo info;
    if (sysinfo(&info) == 0) {
        specs.total_ram_mb = (info.totalram * info.mem_unit) / (1024 * 1024);
    }

    std::ifstream cpu_file("/proc/cpuinfo");
    while (std::getline(cpu_file, line)) {
        if (line.find("model name") != std::string::npos) {
            specs.cpu_model = line.substr(line.find(":") + 2);
            break;
        }
    }

    std::string gpu = exec_cmd("lspci | grep -i 'vga\\|3d\\|display'");
    if (!gpu.empty()) specs.gpu_model = gpu;

#endif

    // Calculate dynamic training score (Simplified)
    if (specs.total_ram_mb > 16000) specs.training_score = 0.9f;
    else if (specs.total_ram_mb > 8000) specs.training_score = 0.7f;
    else specs.training_score = 0.4f;

    return specs;
}

} // namespace emotion
