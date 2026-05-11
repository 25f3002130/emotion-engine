#include "core/Config.h"
#include "core/Logger.h"

namespace emotion {

Config& Config::getInstance() {
    static Config instance;
    return instance;
}

void Config::load(const std::string& path) {
    std::lock_guard<std::mutex> lock(mtx);
    LOG_INFO("Loading configuration from " + path);
    // Simulation of loading JSON settings
    settings["app.version"] = "4.0.2";
    settings["training.max_epochs"] = "1000";
}

std::string Config::get(const std::string& key, const std::string& default_val) {
    std::lock_guard<std::mutex> lock(mtx);
    if (settings.find(key) != settings.end()) {
        return settings.at(key);
    }
    return default_val;
}

int Config::getInt(const std::string& key, int default_val) {
    std::string val = get(key);
    if (val.empty()) return default_val;
    try {
        return std::stoi(val);
    } catch (...) {
        return default_val;
    }
}

} // namespace emotion
