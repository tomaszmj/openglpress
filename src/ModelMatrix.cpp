#include <ModelMatrix.h>
#include <glm/gtc/matrix_transform.hpp>

ModelMatrix::ModelMatrix()
    : translationMatrix(1),
      rotationMatrix(1),
      scaleMatrix(1),
      matrix(1)
{

}

const glm::mat4 &ModelMatrix::get() const
{
    return matrix;
}

const glm::mat4 &ModelMatrix::getTranslation() const
{
    return translationMatrix;
}

const glm::mat4 &ModelMatrix::getRotation() const
{
    return rotationMatrix;
}

const glm::mat4 &ModelMatrix::getScale() const
{
    return scaleMatrix;
}

void ModelMatrix::setTranslation(const glm::vec3 &value)
{
    translationMatrix = glm::translate(glm::mat4(1.0), value);
    update();
}

void ModelMatrix::setRotation(const glm::vec3 &axis, const glm::f32 angle)
{
    rotationMatrix = glm::rotate(glm::mat4(1.0), angle, axis);
    update();
}

void ModelMatrix::setScale(const glm::vec3 &value)
{
    scaleMatrix = glm::scale(glm::mat4(1), value);
    update();
}

void ModelMatrix::update()
{
    matrix = translationMatrix * rotationMatrix * scaleMatrix;
}
