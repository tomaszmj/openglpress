#include <Piston.h>
#include <AnimationParameters.h>

Piston::Piston(const ShaderProgram &shader_program, const VAOWrapper &vao_wrapper,
               const Texture &texture, const glm::vec3 &scale, const AnimationParameters &animation_parameters)
    : RenderedObject(shader_program, vao_wrapper, modelMatrix, texture),
      modelMatrix(), animationParameters(animation_parameters), animationTime(0.0), scale(scale)
{
    modelMatrix.setScale(scale);
    updateTranslation(static_cast<float>(animation_parameters.h[0]));
    lastY = animation_parameters.h[0];
}

Piston::~Piston()
{

}

void Piston::startAnimation()
{

}

#include <iostream>
void Piston::animationStep(double time_diff)
{
    animationTime += time_diff;
//    if(animationTime > animationParameters.t[5])
//        animationTime -= animationParameters.t[5];
    double y = static_cast<double>(animationParameters.calculateY(animationTime));
    updateTranslation(static_cast<float>(y));
    double v = (y - lastY) / time_diff;
    std::cout << animationTime << " " << v << std::endl;
    lastY = y;
}

void Piston::stopAnimation()
{

}

void Piston::updateTranslation(float lower_base_y)
{
    float y = scale.y / 2.0f + lower_base_y;
    modelMatrix.setTranslation(glm::vec3(0.0, y, 0.0));
}
