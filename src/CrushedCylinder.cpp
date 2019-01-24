#include <CrushedCylinder.h>
#include <RenderedObject.h>
#include <AnimationParameters.h>

CrushedCylinder::CrushedCylinder(const ShaderProgram &shader_program, const VAOWrapper &vao_wrapper,
    const Texture &texture, const glm::vec3 &scale,
    const AnimationParameters &animation_parameters, float lower_base_y)
    : RenderedObject(shader_program, vao_wrapper, modelMatrix, texture), modelMatrix(),
      animationParameters(animation_parameters), animationTime(0.0), scale(scale), lowerBaseY(lower_base_y)
{
    updateParameters(static_cast<float>(animationParameters.h[1]));
}

CrushedCylinder::~CrushedCylinder()
{

}

void CrushedCylinder::prepareRender() const
{
    RenderedObject::prepareRender();
}

void CrushedCylinder::animationStep(double time_diff)
{

}

void CrushedCylinder::updateParameters(float upper_base_y)
{
    scale.y = upper_base_y - lowerBaseY;
    float translation_y = upper_base_y - scale.y / 2.0f;
    modelMatrix.setScale(scale);
    modelMatrix.setTranslation(glm::vec3(0.0f, translation_y, 0.0f));
}
