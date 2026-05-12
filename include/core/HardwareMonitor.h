#ifndef HARDWARE_MONITOR_H
#define HARDWARE_MONITOR_H

#include <string>

namespace emotion {

struct HardwareSpecs {
    std::string os_version;
    std::string cpu_model;
    std::string gpu_model;
    int total_ram_mb;
    float training_score; // 0.0 to 1.0 based on capabilities
};

class HardwareMonitor {
public:
    static HardwareSpecs scan();
};

} // namespace emotion

#endif
