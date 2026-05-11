#include "training/TrainingManager.h"
#include "core/Logger.h"

namespace emotion {

TrainingManager::TrainingManager() : is_training(false) {
    LOG_INFO("TrainingManager initialized.");
}

TrainingManager::~TrainingManager() {
    stopTraining();
}

void TrainingManager::addModel(std::unique_ptr<BaseModel> model) {
    LOG_INFO("Model added: " + model->getName());
    models.push_back(std::move(model));
}

void TrainingManager::startTraining(const EmotionVector& target) {
    if (is_training) return;
    is_training = true;
    
    LOG_INFO("Starting global training synchronization...");
    
    training_thread = std::thread([this, target]() {
        while (is_training) {
            for (auto& model : models) {
                float loss = model->train(target);
                if (on_step_callback) {
                    on_step_callback(model->getName(), loss, model->getMaturity());
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    });
}

void TrainingManager::stopTraining() {
    if (!is_training) return;
    is_training = false;
    
    LOG_INFO("Stopping training synchronization...");
    
    if (training_thread.joinable()) {
        training_thread.join();
    }
}

void TrainingManager::setOnStepCallback(std::function<void(std::string, float, float)> callback) {
    on_step_callback = callback;
}

} // namespace emotion
