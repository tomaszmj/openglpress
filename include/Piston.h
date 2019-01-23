#pragma once
#include <RenderedObject.h>
#include <glm/glm.hpp>

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
    virtual void startAnimation() override;
    virtual void animationStep(double time_diff) override;
    virtual void stopAnimation() override;
};
