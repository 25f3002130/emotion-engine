#ifndef HARDWARE_MONITOR_H
#define HARDWARE_MONITOR_H

#include <string>
#include <vector>

namespace emotion {

struct HardwareSpecs {
    std::string cpu_model;
    std::string gpu_info;
    int cpu_cores;
    long total_ram_mb;
    float training_score; // 0.0 to 1.0
    int estimated_minutes;
};

class HardwareMonitor {
public:
    static HardwareSpecs scan();

private:
    static std::string getCPUModel();
    static int getCPUCores();
    static long getTotalRAM();
    static float calculateScore(int cores, long ram);
};

} // namespace emotion

#endif // HARDWARE_MONITOR_H
