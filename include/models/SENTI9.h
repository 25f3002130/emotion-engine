#ifndef SENTI9_H
#define SENTI9_H

#include "BaseModel.h"

namespace emotion {

class SENTI9 : public BaseModel {
public:
    SENTI9();

    std::string getName() const override;
    std::string getDescription() const override;
    
    float train(const EmotionVector& target) override;
    EmotionVector predict() const override;
    float evaluate() override;
    float getMaturity() const override;

    bool save(const std::string& path) const override;
    bool load(const std::string& path) override;
};

} // namespace emotion

#endif // SENTI9_H
