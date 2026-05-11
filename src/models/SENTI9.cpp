#include "models/SENTI9.h"
#include "core/Logger.h"
#include "emotions/EmotionVector.h"
#include <cmath>
#include <iostream>
#include <string>

namespace emotion {

SENTI9::SENTI9() {
  current_state = EmotionVector(0.1f, 0.2f, 0.1f, 0.3f, 0.4f);
  maturity = 12.0f;
  LOG_INFO("SENTI-9 model initialized.");
}

std::string SENTI9::getName() const { return "SENTI-9"; }

std::string SENTI9::getDescription() const {
  return "Advanced neural foundation for high-fidelity emotional resonance.";
}

float SENTI9::train(const EmotionVector &target) {
  float loss = 0.0f;

  auto update = [&](float &current, float target_val) {
    float delta = target_val - current;
    loss += std::abs(delta);
    current += delta * learning_rate * 10.0f;
  };

  update(current_state.serenity, target.serenity);
  update(current_state.euphoria, target.euphoria);
  update(current_state.empathy, target.empathy);
  update(current_state.resilience, target.resilience);
  update(current_state.curiosity, target.curiosity);

  current_state.normalize();

  if (maturity < 100.0f)
    maturity += 0.05f;

  return loss / 5.0f;
}

EmotionVector SENTI9::predict() const { return current_state; }

float SENTI9::evaluate() { return current_state.getAggregate(); }

float SENTI9::getMaturity() const { return maturity; }

bool SENTI9::save(const std::string &path) const {
  LOG_INFO("Saving SENTI-9 state to " + path);
  return true;
}

bool SENTI9::load(const std::string &path) {
  LOG_INFO("Loading SENTI-9 state from " + path);
  return true;
}

} // namespace emotion
