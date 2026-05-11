#include "core/DataManager.h"
#include "core/Logger.h"
#include <iostream>

namespace emotion {

DataManager& DataManager::getInstance() {
    static DataManager instance;
    return instance;
}

bool DataManager::saveModel(const BaseModel& model, const std::string& path) {
    LOG_INFO("Persistence Layer: Saving model '" + model.getName() + "' to " + path);
    return model.save(path);
}

bool DataManager::loadModel(BaseModel& model, const std::string& path) {
    LOG_INFO("Persistence Layer: Loading model '" + model.getName() + "' from " + path);
    return model.load(path);
}

} // namespace emotion
