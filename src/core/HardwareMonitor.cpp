#include "core/HardwareMonitor.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>

namespace emotion {

std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) return "";
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

HardwareSpecs HardwareMonitor::scan() {
    HardwareSpecs specs;
    specs.cpu_model = getCPUModel();
    specs.cpu_cores = getCPUCores();
    specs.total_ram_mb = getTotalRAM();
    
    // GPU Detection via lspci
    std::string gpu_raw = exec("lspci | grep -E 'VGA|3D'");
    if (gpu_raw.empty()) {
        specs.gpu_info = "Integrated Graphics (Generic)";
    } else {
        // Simple parsing of lspci output
        size_t pos = gpu_raw.find("controller: ");
        if (pos != std::string::npos) {
            specs.gpu_info = gpu_raw.substr(pos + 12);
        } else {
            specs.gpu_info = gpu_raw;
        }
        // Trim newline
        specs.gpu_info.erase(std::remove(specs.gpu_info.begin(), specs.gpu_info.end(), '\n'), specs.gpu_info.end());
    }

    specs.training_score = calculateScore(specs.cpu_cores, specs.total_ram_mb);
    
    // Boost score if dedicated GPU is found (Simplified check)
    if (specs.gpu_info.find("NVIDIA") != std::string::npos || specs.gpu_info.find("AMD") != std::string::npos) {
        specs.training_score = std::min(1.0f, specs.training_score + 0.2f);
    }

    specs.estimated_minutes = static_cast<int>(60.0f * (1.5f - specs.training_score));
    
    return specs;
}

std::string HardwareMonitor::getCPUModel() {
    std::ifstream file("/proc/cpuinfo");
    std::string line;
    while (std::getline(file, line)) {
        if (line.find("model name") != std::string::npos) {
            size_t pos = line.find(":");
            if (pos != std::string::npos) {
                return line.substr(pos + 2);
            }
        }
    }
    return "Generic CPU";
}

int HardwareMonitor::getCPUCores() {
    std::ifstream file("/proc/cpuinfo");
    std::string line;
    int cores = 0;
    while (std::getline(file, line)) {
        if (line.find("processor") != std::string::npos) {
            cores++;
        }
    }
    return cores > 0 ? cores : 1;
}

long HardwareMonitor::getTotalRAM() {
    std::ifstream file("/proc/meminfo");
    std::string line;
    if (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string label;
        long kb;
        ss >> label >> kb;
        return kb / 1024;
    }
    return 4096;
}

float HardwareMonitor::calculateScore(int cores, long ram) {
    float core_score = std::min(1.0f, static_cast<float>(cores) / 16.0f);
    float ram_score = std::min(1.0f, static_cast<float>(ram) / 32768.0f);
    return (core_score * 0.6f) + (ram_score * 0.4f);
}

} // namespace emotion
