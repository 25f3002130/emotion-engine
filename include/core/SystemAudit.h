#ifndef SYSTEM_AUDIT_H
#define SYSTEM_AUDIT_H

#include <string>
#include <vector>

namespace emotion {

struct ModelInfo {
    std::string name;
    std::string description;
    std::string path;
    bool is_experimental;
};

struct AuditResult {
    bool integrity_pass;
    bool update_available;
    std::string latest_version;
    std::vector<ModelInfo> available_models;
    std::vector<std::string> errors;
};

class SystemAudit {
public:
    static AuditResult performFullAudit();

private:
    static bool checkIntegrity(std::vector<std::string>& errors);
    static bool checkForUpdates(std::string& latest);
    static std::vector<ModelInfo> discoverModels();
};

} // namespace emotion

#endif // SYSTEM_AUDIT_H
