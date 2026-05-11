#include "core/Logger.h"
#include <iostream>
#include <chrono>
#include <iomanip>

namespace emotion {

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

void Logger::log(Level level, const std::string& message) {
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

    std::string level_str;
    switch (level) {
        case Level::DEBUG: level_str = "[DEBUG]"; break;
        case Level::INFO:  level_str = "[INFO] "; break;
        case Level::WARN:  level_str = "[WARN] "; break;
        case Level::ERROR: level_str = "[ERROR]"; break;
    }

    std::cout << std::put_time(std::localtime(&time_t), "%H:%M:%S")
              << "." << std::setfill('0') << std::setw(3) << ms.count()
              << " " << level_str << " " << message << std::endl;
}

} // namespace emotion
