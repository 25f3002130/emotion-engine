#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#include "models/BaseModel.h"
#include <string>

namespace emotion {

class DataManager {
public:
    static DataManager& getInstance();

    bool saveModel(const BaseModel& model, const std::string& path);
    bool loadModel(BaseModel& model, const std::string& path);

private:
    DataManager() = default;
};

} // namespace emotion

#endif // DATA_MANAGER_H
