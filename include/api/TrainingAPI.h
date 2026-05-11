#ifndef TRAINING_API_H
#define TRAINING_API_H

#include "crow_all.h" // Assuming crow_all.h is available or integrated
#include "training/TrainingManager.h"
#include <memory>

namespace emotion {

class TrainingAPI {
public:
    TrainingAPI(TrainingManager& manager) : m_manager(manager) {}

    void setupRoutes(crow::SimpleApp& app) {
        CROW_ROUTE(app, "/api/v1/training/start").methods("POST"_method)([this](const crow::request& req) {
            EmotionVector target(0.9f, 0.8f, 0.95f, 0.75f, 0.9f);
            m_manager.startTraining(target);
            return crow::response(200, "Training Started");
        });

        CROW_ROUTE(app, "/api/v1/training/stop").methods("POST"_method)([this](const crow::request& req) {
            m_manager.stopTraining();
            return crow::response(200, "Training Stopped");
        });

        CROW_ROUTE(app, "/api/v1/metrics/performance")([this]() {
            crow::json::wvalue x;
            x["tflops"] = 42.8;
            x["sync"] = 89.4;
            x["drift"] = 0.02;
            return x;
        });
    }

private:
    TrainingManager& m_manager;
};

} // namespace emotion

#endif // TRAINING_API_H
