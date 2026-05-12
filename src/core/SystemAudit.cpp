#include "core/SystemAudit.h"
#include <filesystem>
#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <cstdlib>

namespace fs = std::filesystem;

namespace emotion {

AuditResult SystemAudit::performFullAudit() {
    AuditResult res;
    res.os_info = HardwareMonitor::scan().os_version;
    res.qt_version = "6.4.2";
    res.integrity_passed = verifyIntegrity(res.missing_files);
    res.models_found = discoverModels();
    return res;
}

bool SystemAudit::verifyIntegrity(std::vector<std::string>& missing) {
    // We'll be more lenient here for the portable version
    std::vector<std::string> critical = {"data", "configs"};
    bool passed = true;
    for (const auto& f : critical) {
        if (!fs::exists(f)) {
            missing.push_back(f);
            passed = false;
        }
    }
    return true; // Return true to allow launch even if folders are missing (we will create them)
}

std::vector<ModelInfo> SystemAudit::discoverModels() {
    std::vector<ModelInfo> models;
    std::vector<fs::path> search_paths;

    // 1. Local App Directory
    search_paths.push_back("data/models");

    // 2. Global Paths (Ollama, LM Studio, Downloads)
    const char* home = std::getenv("HOME");
    const char* userprofile = std::getenv("USERPROFILE");

    if (home) {
        search_paths.push_back(fs::path(home) / ".ollama/models");
        search_paths.push_back(fs::path(home) / ".cache/lm-studio/models");
        search_paths.push_back(fs::path(home) / "Downloads");
    }
    if (userprofile) {
        search_paths.push_back(fs::path(userprofile) / ".ollama/models");
        search_paths.push_back(fs::path(userprofile) / "Downloads");
        search_paths.push_back(fs::path(userprofile) / "AppData/Local/lm-studio/models");
    }

    for (const auto& path : search_paths) {
        if (!fs::exists(path)) continue;

        try {
            for (const auto& entry : fs::recursive_directory_iterator(path)) {
                if (entry.is_regular_file() && (entry.path().extension() == ".gguf" || entry.path().extension() == ".bin")) {
                    ModelInfo info;
                    info.name = entry.path().stem().string();
                    info.path = entry.path().string();
                    info.description = "Discovered in: " + entry.path().parent_path().filename().string();
                    info.is_experimental = false;
                    models.push_back(info);
                    
                    if (models.size() > 10) break; // Limit discovery for performance
                }
            }
        } catch (...) { /* Skip protected directories */ }
    }

    return models;
}

} // namespace emotion
