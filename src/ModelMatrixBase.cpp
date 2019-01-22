#include <ModelMatrixBase.h>
#include <glm/gtc/matrix_transform.hpp>

ModelMatrixBase::ModelMatrixBase()
    : translationMatrix(1),
      rotationMatrix(1),
      scaleMatrix(1),
      matrix(1)
{

}

ModelMatrixBase::~ModelMatrixBase()
{

}

void ModelMatrixBase::startAnimation()
{

}

void ModelMatrixBase::animationStep(double)
{

}

void ModelMatrixBase::stopAnimation()
{

}

const glm::mat4 &ModelMatrixBase::get() const
{
    return matrix;
}

const glm::mat4 &ModelMatrixBase::getTranslation() const
{
    return translationMatrix;
}

const glm::mat4 &ModelMatrixBase::getRotation() const
{
    return rotationMatrix;
}

const glm::mat4 &ModelMatrixBase::getScale() const
{
    return scaleMatrix;
}

void ModelMatrixBase::setTranslation(const glm::vec3 &value)
{
    translationMatrix = glm::translate(glm::mat4(1.0), value);
    update();
}

void ModelMatrixBase::setRotation(const glm::vec3 &axis, const glm::f32 angle)
{
    rotationMatrix = glm::rotate(glm::mat4(1.0), angle, axis);
    update();
}

void ModelMatrixBase::setScale(const glm::vec3 &value)
{
    scaleMatrix = glm::scale(glm::mat4(1), value);
    update();
}

void ModelMatrixBase::update()
{
    matrix = translationMatrix * rotationMatrix * scaleMatrix;
}
