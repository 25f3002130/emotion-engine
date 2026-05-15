#include "emotions/EmotionProcessor.h"
#include "core/Logger.h"
#include <algorithm>

namespace emotion {

EmotionProcessor::EmotionProcessor() {
    LOG_INFO("EmotionProcessor initialized.");
}

EmotionVector EmotionProcessor::processInput(const std::string& input) {
    LOG_DEBUG("Processing input: " + input);
    return EmotionVector(0.7f, 0.6f, 0.5f, 0.8f, 0.4f);
}

float EmotionProcessor::calculateEmpathy(const EmotionVector& a, const EmotionVector& b) {
    float diff = std::abs(a.empathy - b.empathy) + 
                 std::abs(a.serenity - b.serenity);
    return std::max(0.0f, 1.0f - (diff / 2.0f));
}

} 
