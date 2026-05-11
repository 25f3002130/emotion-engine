#ifndef EMOTION_PROCESSOR_H
#define EMOTION_PROCESSOR_H

#include "emotions/EmotionVector.h"
#include <string>

namespace emotion {

class EmotionProcessor {
public:
    EmotionProcessor();

    /**
     * @brief Process raw input and extract emotional context
     */
    EmotionVector processInput(const std::string& input);

    /**
     * @brief Calculate empathy score between two emotional states
     */
    float calculateEmpathy(const EmotionVector& a, const EmotionVector& b);
};

} // namespace emotion

#endif // EMOTION_PROCESSOR_H
