#include "core/SystemAudit.h"
#include <fstream>
#include <filesystem>
#include <iostream>
#include <cstdio>
#include <memory>
#include <array>
#include <vector>
#include <string>

namespace emotion {

namespace fs = std::filesystem;

AuditResult SystemAudit::performFullAudit() {
    AuditResult result;
    result.integrity_pass = checkIntegrity(result.errors);
    result.update_available = checkForUpdates(result.latest_version);
    result.available_models = discoverModels();
    return result;
}

bool SystemAudit::checkIntegrity(std::vector<std::string>& errors) {
    std::vector<std::string> critical_files = {
        "emotion_engine",
        "Makefile",
        "configs/default_config.json",
        "assets/splash.png"
    };

    bool pass = true;
    for (const auto& file : critical_files) {
        if (!fs::exists(file)) {
            errors.push_back("Missing critical file: " + file);
            pass = false;
        }
    }
    return pass;
}

bool SystemAudit::checkForUpdates(std::string& latest) {
    latest = "v4.0.2";
    return false;
}

std::vector<emotion::ModelInfo> SystemAudit::discoverModels() {
    std::vector<emotion::ModelInfo> models;
    fs::path model_dir = "data/models";
    
    if (!fs::exists(model_dir)) {
        fs::create_directories(model_dir);
        return models;
    }

    for (const auto& entry : fs::directory_iterator(model_dir)) {
        if (entry.path().extension() == ".bin") {
            emotion::ModelInfo m;
            m.path = entry.path().string();
            m.name = entry.path().stem().string();
            m.description = "Local Neural Weights detected.";
            m.is_experimental = (m.name.find("X") != std::string::npos || m.name.find("exp") != std::string::npos);
            
            // Modern filesystem path joining
            fs::path json_path = entry.path().parent_path() / (m.name + ".json");
            
            if (fs::exists(json_path)) {
                std::ifstream jf(json_path);
                std::string line;
                while (std::getline(jf, line)) {
                    if (line.find("description") != std::string::npos) {
                        size_t start = line.find(": \"");
                        if (start != std::string::npos) {
                            start += 3;
                            size_t end = line.find_last_of("\"");
                            if (end != std::string::npos && end > start) {
                                m.description = line.substr(start, end - start);
                            }
                        }
                    }
                }
            }
            models.push_back(m);
        }
    }
    return models;
}

} // namespace emotion
