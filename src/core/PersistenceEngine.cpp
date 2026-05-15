#include "core/PersistenceEngine.h"
#include "core/Logger.h"
#include <fstream>
#include <filesystem>
#include <sstream>

namespace fs = std::filesystem;

namespace emotion {

PersistenceEngine& PersistenceEngine::getInstance() {
    static PersistenceEngine instance;
    return instance;
}

bool PersistenceEngine::loadMetadata(ModelInfo& info) {
    std::string metaPath = info.path + ".meta";
    if (!fs::exists(metaPath)) {
        // Initial state for new models
        info.maturity = 0.05f; 
        info.training_cycles = 0;
        info.prerequisites = {1, 1, 0}; // Default starter prerequisites
        return false;
    }

    std::ifstream f(metaPath);
    if (f.is_open()) {
        f >> info.maturity >> info.training_cycles;
        f >> info.prerequisites.recognition;
        f >> info.prerequisites.tone_sensitivity;
        f >> info.prerequisites.abstract_context;
        return true;
    }
    return false;
}

bool PersistenceEngine::saveMetadata(const ModelInfo& info) {
    std::string metaPath = info.path + ".meta";
    std::ofstream f(metaPath);
    if (f.is_open()) {
        f << info.maturity << " " << info.training_cycles << "\n";
        f << info.prerequisites.recognition << " ";
        f << info.prerequisites.tone_sensitivity << " ";
        f << info.prerequisites.abstract_context << "\n";
        return true;
    }
    return false;
}

void PersistenceEngine::addLogEntry(const TrainingLogEntry& entry) {
    std::ofstream f("data/evolution.log", std::ios::app);
    if (f.is_open()) {
        f << entry.timestamp << "|" << entry.model_name << "|" 
          << entry.action << "|" << entry.result << "|" << entry.status << "\n";
    }
}

std::vector<TrainingLogEntry> PersistenceEngine::getLogs() {
    std::vector<TrainingLogEntry> logs;
    std::ifstream f("data/evolution.log");
    std::string line;
    while (std::getline(f, line)) {
        std::stringstream ss(line);
        std::string item;
        TrainingLogEntry e;
        std::getline(ss, e.timestamp, '|');
        std::getline(ss, e.model_name, '|');
        std::getline(ss, e.action, '|');
        std::getline(ss, item, '|');
        try { e.result = std::stof(item); } catch(...) { e.result = 0; }
        std::getline(ss, e.status, '|');
        logs.push_back(e);
    }
    return logs;
}

bool PersistenceEngine::saveModel(const BaseModel& model, const std::string& path) {
    return model.save(path);
}

bool PersistenceEngine::loadModel(BaseModel& model, const std::string& path) {
    return model.load(path);
}

} // namespace emotion
