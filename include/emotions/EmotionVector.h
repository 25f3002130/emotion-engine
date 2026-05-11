#ifndef EMOTION_VECTOR_H
#define EMOTION_VECTOR_H

#include <string>
#include <vector>

namespace emotion {

/**
 * @brief Represents a 5-dimensional emotional state.
 * Dimensions: Serenity, Euphoria, Empathy, Resilience, Curiosity.
 */
struct EmotionVector {
    float serenity;      // Emotional stability (0.0-1.0)
    float euphoria;      // Positive emotion (0.0-1.0)
    float empathy;       // Understanding others (0.0-1.0)
    float resilience;    // Stress recovery (0.0-1.0)
    float curiosity;     // Exploratory drive (0.0-1.0)

    EmotionVector() 
        : serenity(0.5f), euphoria(0.5f), empathy(0.5f), resilience(0.5f), curiosity(0.5f) {}

    EmotionVector(float s, float eu, float em, float r, float c)
        : serenity(s), euphoria(eu), empathy(em), resilience(r), curiosity(c) {}

    /**
     * @brief Get the aggregate emotional mastery score (0.0-1.0)
     */
    float getAggregate() const {
        return (serenity + euphoria + empathy + resilience + curiosity) / 5.0f;
    }

    /**
     * @brief Normalize all values to [0.0, 1.0]
     */
    void normalize() {
        auto clamp = [](float& val) {
            if (val < 0.0f) val = 0.0f;
            if (val > 1.0f) val = 1.0f;
        };
        clamp(serenity);
        clamp(euphoria);
        clamp(empathy);
        clamp(resilience);
        clamp(curiosity);
    }

    std::string toString() const {
        return "Serenity: " + std::to_string(serenity) + 
               ", Euphoria: " + std::to_string(euphoria) + 
               ", Empathy: " + std::to_string(empathy) + 
               ", Resilience: " + std::to_string(resilience) + 
               ", Curiosity: " + std::to_string(curiosity);
    }
};

} // namespace emotion

#endif // EMOTION_VECTOR_H
