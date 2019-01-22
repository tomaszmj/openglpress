#pragma once
#include <glm/glm.hpp>

class ModelMatrixBase
{
public:
    ModelMatrixBase();
    virtual ~ModelMatrixBase();
    virtual void startAnimation();
    virtual void animationStep(double time_diff);
    virtual void stopAnimation();
    const glm::mat4 &get() const;
    const glm::mat4 &getTranslation() const;
    const glm::mat4 &getRotation() const;
    const glm::mat4 &getScale() const;
    void setTranslation(const glm::vec3 &value);
    void setRotation(const glm::vec3 &axis, const glm::f32 angle);
    void setScale(const glm::vec3 &value);

protected:
    glm::mat4 translationMatrix;
    glm::mat4 rotationMatrix;
    glm::mat4 scaleMatrix;
    glm::mat4 matrix;

    void update();
};
