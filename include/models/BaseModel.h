#ifndef BASE_MODEL_H
#define BASE_MODEL_H

#include "emotions/EmotionVector.h"
#include <string>
#include <memory>

namespace emotion {

class BaseModel {
public:
    virtual ~BaseModel() = default;

    virtual std::string getName() const = 0;
    virtual std::string getDescription() const = 0;
    
    /**
     * @brief Perform one training epoch
     * @param target Target emotional state
     * @return New loss value
     */
    virtual float train(const EmotionVector& target) = 0;

    /**
     * @brief Predict current emotional state
     */
    virtual EmotionVector predict() const = 0;

    /**
     * @brief Evaluate performance against validation data
     */
    virtual float evaluate() = 0;

    /**
     * @brief Get model maturity percentage
     */
    virtual float getMaturity() const = 0;

    // Serialization
    virtual bool save(const std::string& path) const = 0;
    virtual bool load(const std::string& path) = 0;

protected:
    EmotionVector current_state;
    float learning_rate = 0.001f;
    float maturity = 0.0f;
};

} // namespace emotion

#endif // BASE_MODEL_H
