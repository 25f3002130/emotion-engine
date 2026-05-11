#ifndef LOGGER_H
#define LOGGER_H

#include <string>

namespace emotion {

class Logger {
public:
    enum class Level {
        DEBUG,
        INFO,
        WARN,
        ERROR
    };

    static Logger& getInstance();

    void log(Level level, const std::string& message);

private:
    Logger() = default;
};

// Convenience macros
#define LOG_INFO(msg) emotion::Logger::getInstance().log(emotion::Logger::Level::INFO, msg)
#define LOG_ERROR(msg) emotion::Logger::getInstance().log(emotion::Logger::Level::ERROR, msg)
#define LOG_DEBUG(msg) emotion::Logger::getInstance().log(emotion::Logger::Level::DEBUG, msg)

} // namespace emotion

#endif // LOGGER_H
