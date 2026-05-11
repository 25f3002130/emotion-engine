#ifndef TRAINING_MANAGER_H
#define TRAINING_MANAGER_H

#include "models/BaseModel.h"
#include <vector>
#include <memory>
#include <thread>
#include <atomic>
#include <functional>
#include <string>

namespace emotion {

class TrainingManager {
public:
    TrainingManager();
    ~TrainingManager();

    void addModel(std::unique_ptr<BaseModel> model);
    void startTraining(const EmotionVector& target);
    void stopTraining();

    void setOnStepCallback(std::function<void(std::string, float, float)> callback);

private:
    std::vector<std::unique_ptr<BaseModel>> models;
    std::thread training_thread;
    std::atomic<bool> is_training;
    std::function<void(std::string, float, float)> on_step_callback;
};

} // namespace emotion

#endif // TRAINING_MANAGER_H
