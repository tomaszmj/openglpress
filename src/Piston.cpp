#include <Piston.h>

Piston::~Piston()
{

}

void Piston::animationStep(double time_diff)
{
    animationTime += time_diff;
    if(animationTime > animationParameters.t[5])
        animationTime -= animationParameters.t[5];
    double y = animationParameters.calculateY(animationTime);
    updateTranslation(static_cast<float>(y));
}

void Piston::updateTranslation(float lower_base_y)
{
    float translation_y = scale.y / 2.0f + lower_base_y;
    modelMatrixInstance.setTranslation(glm::vec3(0.0f, translation_y, 0.0f));
}
