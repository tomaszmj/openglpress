#include <Piston.h>
#include <AnimationParameters.h>

Piston::Piston(const ShaderProgram &shader_program, const VAOWrapper &vao_wrapper,
               const Texture &texture, const glm::vec3 &scale, const AnimationParameters &animation_parameters)
    : RenderedObject(shader_program, vao_wrapper, modelMatrixInstance, texture),
      modelMatrixInstance(), animationParameters(animation_parameters), animationTime(0.0), scale(scale)
{
    modelMatrixInstance.setScale(scale);
    updateTranslation(static_cast<float>(animation_parameters.h[0]));
}

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
