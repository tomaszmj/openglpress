#pragma once
#include <RenderedObject.h>
#include <ModelMatrix.h>
#include <AnimationParameters.h>

class ShaderProgram;
class VAOWrapper;
class Texture;
class AnimationParameters;

class CrushedCylinder: public RenderedObject
{
public:
    CrushedCylinder(const ShaderProgram &shader_program, const VAOWrapper &vao_wrapper,
        const Texture &texture, const glm::vec3 &scale,
        const AnimationParameters &animation_parameters, float lower_base_y)
        : RenderedObject(shader_program, vao_wrapper, modelMatrixInstance, texture), modelMatrixInstance(),
          animationParameters(animation_parameters), animationTime(0.0), scale(scale), lowerBaseY(lower_base_y)
    {
        updateParameters(static_cast<float>(animationParameters.h[1]));
    }

    virtual ~CrushedCylinder() override;
    virtual void prepareRender() const override;
    virtual void animationStep(double time_diff) override;

protected:
    ModelMatrix modelMatrixInstance;
    const AnimationParameters &animationParameters;
    double animationTime;
    glm::vec3 scale;
    const float lowerBaseY;

    void updateParameters(float upper_base_y);
};
