#include "Camera.h"

Camera::Camera(glm::vec3 eye, glm::vec3 lookingAt)
    : position(eye)
{
}

const glm::mat4 &Camera::getViewMatrix() const
{
}

void Camera::moveRightOrLeft(glm::f32 coefficient)
{
}

void Camera::moveForwardOrBackward(glm::f32 coefficient)
{
}

void Camera::moveUpOrDown(glm::f32 coefficient)
{
}
