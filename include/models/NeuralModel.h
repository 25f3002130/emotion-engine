#ifndef NEURAL_MODEL_H
#define NEURAL_MODEL_H

#include "models/BaseModel.h"
#include "core/SystemAudit.h"

namespace emotion {

class NeuralModel : public BaseModel {
public:
    explicit NeuralModel(const ModelInfo& info);

    std::string getName() const override;
    std::string getDescription() const override;
    
    float train(const EmotionVector& target) override;
    EmotionVector predict() const override;
    float evaluate() override;
    
    float getMaturity() const override;
    const ModelInfo& getInfo() const { return metadata; }

    bool save(const std::string& path) const override;
    bool load(const std::string& path) override;

private:
    ModelInfo metadata;
    float current_accuracy;
};

} // namespace emotion

#endif
