#pragma once
#include <RenderedObject.h>
#include <glm/glm.hpp>
#include <ModelMatrix.h>

class ShaderProgram;
class VAOWrapper;
class Texture;
class AnimationParameters;

class Piston: public RenderedObject
{
public:
    Piston(const ShaderProgram &shader_program, const VAOWrapper &vao_wrapper, const Texture &texture,
        const glm::vec3 &scale, const AnimationParameters &animation_parameters);
    virtual ~Piston() override;
    virtual void animationStep(double time_diff) override;

protected:
    ModelMatrix modelMatrix;
    const AnimationParameters &animationParameters;
    double animationTime;
    const glm::vec3 scale;

    void updateTranslation(float lower_base_y);
};
