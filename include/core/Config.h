#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <map>
#include <mutex>

namespace emotion {

class Config {
public:
    static Config& getInstance();

    void load(const std::string& path);
    std::string get(const std::string& key, const std::string& default_val = "");
    int getInt(const std::string& key, int default_val = 0);

private:
    Config() = default;
    Config(const Config&) = delete;
    Config& operator=(const Config&) = delete;

    std::map<std::string, std::string> settings;
    std::mutex mtx;
};

} // namespace emotion

#endif // CONFIG_H
