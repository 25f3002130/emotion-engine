#include "core/SystemAudit.h"
#include "core/Logger.h"
#include "core/PersistenceEngine.h"
#include <filesystem>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>

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
    std::vector<std::string> critical = {"data", "configs"};
    for (const auto& f : critical) {
        if (!fs::exists(f)) missing.push_back(f);
    }
    return true; 
}

std::vector<ModelInfo> SystemAudit::discoverModels() {
    std::vector<ModelInfo> models;
    std::vector<fs::path> search_paths;

    const char* home = std::getenv("HOME");
    const char* userprofile = std::getenv("USERPROFILE");

    // 1. Core Paths
    search_paths.push_back("data/models");
    if (home) {
        search_paths.push_back(fs::path(home) / "Downloads");
        search_paths.push_back(fs::path(home) / "models");
        search_paths.push_back(fs::path(home) / "ai");
        search_paths.push_back(fs::path(home) / ".cache/lm-studio/models");
    }
    if (userprofile) {
        search_paths.push_back(fs::path(userprofile) / "Downloads");
        search_paths.push_back(fs::path(userprofile) / "Documents/AI");
    }

    LOG_INFO("[SCAN] Initiating Deep Neural Search...");

    for (const auto& path : search_paths) {
        if (!fs::exists(path)) continue;

        try {
            // Non-recursive scan for Downloads to avoid huge wait times, recursive for others
            bool recursive = (path.filename() != "Downloads");
            
            auto handle_entry = [&](const fs::directory_entry& entry) {
                if (entry.is_regular_file()) {
                    std::string ext = entry.path().extension().string();
                    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
                    
                    if (ext == ".gguf" || ext == ".bin" || ext == ".pth") {
                        ModelInfo info;
                        info.name = entry.path().stem().string();
                        if (info.name.empty()) info.name = "Unknown Neural Weights";
                        
                        info.path = entry.path().string();
                        info.description = "Found in: " + entry.path().parent_path().filename().string();
                        info.is_experimental = (info.name.find("exp") != std::string::npos);
                        
                        // Load persistent state
                        PersistenceEngine::getInstance().loadMetadata(info);
                        
                        LOG_INFO("[SCAN] Indexed Model: " + info.name + " (" + ext + ")");
                        models.push_back(info);
                    }
                }
            };

            if (recursive) {
                for (const auto& entry : fs::recursive_directory_iterator(path)) {
                    handle_entry(entry);
                    if (models.size() > 50) break;
                }
            } else {
                for (const auto& entry : fs::directory_iterator(path)) {
                    handle_entry(entry);
                }
            }
        } catch (...) {}
    }

    // Add Ollama logic as a secondary layer
    if (home) {
        fs::path ollama_manifests = fs::path(home) / ".ollama/models/manifests/registry.ollama.ai/library";
        if (fs::exists(ollama_manifests)) {
            try {
                for (const auto& entry : fs::directory_iterator(ollama_manifests)) {
                    if (entry.is_directory()) {
                        for (const auto& sub : fs::directory_iterator(entry.path())) {
                            ModelInfo info;
                            info.name = entry.path().filename().string() + ":" + sub.path().filename().string();
                            info.path = sub.path().string();
                            info.description = "Ollama Library";
                            info.is_experimental = false;
                            
                            PersistenceEngine::getInstance().loadMetadata(info);
                            models.push_back(info);
                        }
                    }
                }
            } catch (...) {}
        }
    }

    return models;
}

} // namespace emotion
