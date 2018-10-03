#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(glm::vec3 eye, glm::vec3 lookingAt, glm::vec3 move_velocity)
    : moveVelocity(move_velocity), up(0.0f, 1.0f, 0.0f), sightDirection(glm::normalize(eye - lookingAt)),
      viewMatrix(glm::lookAt(eye, lookingAt, up))
{
}

void Camera::move(glm::f32 coefficient, Direction direction)
{
    switch(direction)
    {
        case LEFT: moveRightOrLeft(-coefficient); break;
        case RIGHT: moveRightOrLeft(coefficient); break;
        case DOWN: moveUpOrDown(-coefficient); break;
        case UP: moveUpOrDown(coefficient); break;
        case FORWARD: moveBackwardOrForward(-coefficient); break;
        case BACKWARD: moveBackwardOrForward(coefficient);
    }
}

const glm::mat4 &Camera::getViewMatrix() const
{
    return viewMatrix;
}

void Camera::moveRightOrLeft(glm::f32 coefficient)
{
    glm::vec3 translation = coefficient * moveVelocity.x * glm::cross(sightDirection, up);
    viewMatrix = glm::translate(viewMatrix, translation);
}

void Camera::moveBackwardOrForward(glm::f32 coefficient)
{
    glm::vec3 translation = coefficient * moveVelocity.z * sightDirection;
    viewMatrix = glm::translate(viewMatrix, translation);
}

void Camera::moveUpOrDown(glm::f32 coefficient)
{
    glm::vec3 translation = coefficient * moveVelocity.y * glm::cross(glm::cross(sightDirection, up), sightDirection);
    viewMatrix = glm::translate(viewMatrix, translation);
}
