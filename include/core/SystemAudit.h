#ifndef SYSTEM_AUDIT_H
#define SYSTEM_AUDIT_H

#include <string>
#include <vector>
#include "core/HardwareMonitor.h"

namespace emotion {

struct ModelPrerequisites {
    int recognition = 0;       // 0: Missing, 1: Low, 2: Calibrated
    int tone_sensitivity = 0;
    int abstract_context = 0;
};

struct ModelInfo {
    std::string name;
    std::string path;
    std::string description;
    bool is_experimental;
    
    // Persistent Stats
    float maturity = 0.0f;
    int training_cycles = 0;
    ModelPrerequisites prerequisites;
};

struct AuditResult {
    std::string os_info;
    std::string qt_version;
    bool integrity_passed;
    std::vector<std::string> missing_files;
    std::vector<ModelInfo> models_found;
};

class SystemAudit {
public:
    static AuditResult performFullAudit();
    static bool verifyIntegrity(std::vector<std::string>& missing);
    static std::vector<ModelInfo> discoverModels();
};

} // namespace emotion

#endif
