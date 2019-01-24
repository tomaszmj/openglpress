#include <CrushedCylinder.h>
#include <RenderedObject.h>
#include <ShaderProgram.h>

CrushedCylinder::~CrushedCylinder()
{

}

void CrushedCylinder::prepareRender() const
{
    RenderedObject::prepareRender();
    float crushing_factor = scale.y / (static_cast<float>(animationParameters.h[1]) - lowerBaseY);
    assert(crushing_factor > 0.0f && crushing_factor <= 1.0f);
    float rmax = 1.0f / (2.0f * std::sqrt(crushing_factor));
    shaderProgram.setFloatUniform("crushing_factor", crushing_factor);
    shaderProgram.setFloatUniform("rmax", rmax);
}

void CrushedCylinder::animationStep(double time_diff)
{
    animationTime += time_diff;
    if(animationTime > animationParameters.t[5])
        animationTime -= animationParameters.t[5];
    double y = animationParameters.calculateY(animationTime);
    if(y >= animationParameters.h[2] && y <= animationParameters.h[1])
        updateParameters(static_cast<float>(y));
}

void CrushedCylinder::updateParameters(float upper_base_y)
{
    scale.y = upper_base_y - lowerBaseY;
    float translation_y = upper_base_y - scale.y / 2.0f;
    modelMatrixInstance.setScale(scale);
    modelMatrixInstance.setTranslation(glm::vec3(0.0f, translation_y, 0.0f));
}
