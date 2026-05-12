#include "core/HardwareMonitor.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>
#include <QtCore/QtGlobal>
#include <QtCore/QString>

namespace emotion {

std::string exec_cmd(const char* cmd) {
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
    specs.gpu_info = getGPUInfo();
    specs.os_info = getOSInfo();
    specs.qt_version = getQtVersion();

    // Scoring logic: 16 cores + 32GB RAM + Dedicated GPU = 1.0
    float core_score = std::min(1.0f, static_cast<float>(specs.cpu_cores) / 16.0f);
    float ram_score = std::min(1.0f, static_cast<float>(specs.total_ram_mb) / 32768.0f);
    specs.training_score = (core_score * 0.4f) + (ram_score * 0.3f);
    
    if (specs.gpu_info.find("NVIDIA") != std::string::npos || specs.gpu_info.find("AMD") != std::string::npos) {
        specs.training_score += 0.3f;
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

std::string HardwareMonitor::getGPUInfo() {
    std::string gpu_raw = exec_cmd("lspci | grep -E 'VGA|3D'");
    if (gpu_raw.empty()) return "Integrated Graphics";
    size_t pos = gpu_raw.find("controller: ");
    std::string info = (pos != std::string::npos) ? gpu_raw.substr(pos + 12) : gpu_raw;
    info.erase(std::remove(info.begin(), info.end(), '\n'), info.end());
    return info;
}

std::string HardwareMonitor::getOSInfo() {
    std::ifstream file("/etc/os-release");
    std::string line;
    while (std::getline(file, line)) {
        if (line.find("PRETTY_NAME=") != std::string::npos) {
            size_t pos = line.find("=");
            return line.substr(pos + 2, line.length() - pos - 3);
        }
    }
    return "Linux Generic";
}

std::string HardwareMonitor::getQtVersion() {
    return QString(QT_VERSION_STR).toStdString();
}

} // namespace emotion
