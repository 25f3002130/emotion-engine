#ifndef PERSISTENCE_ENGINE_H
#define PERSISTENCE_ENGINE_H

#include "models/BaseModel.h"
#include "core/SystemAudit.h"
#include <string>
#include <vector>

namespace emotion {

struct TrainingLogEntry {
    std::string timestamp;
    std::string model_name;
    std::string action; // "TRAINING", "TEST"
    float result;
    std::string status;
};

class PersistenceEngine {
public:
    static PersistenceEngine& getInstance();

    // Metadata management for discovered models
    bool loadMetadata(ModelInfo& info);
    bool saveMetadata(const ModelInfo& info);

    // Training history management
    void addLogEntry(const TrainingLogEntry& entry);
    std::vector<TrainingLogEntry> getLogs();

    // Legacy support
    bool saveModel(const BaseModel& model, const std::string& path);
    bool loadModel(BaseModel& model, const std::string& path);

private:
    PersistenceEngine() = default;
    std::string getMetadataPath(const std::string& modelPath);
};

} // namespace emotion

#endif
