#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(glm::vec3 eye, glm::vec3 lookingAt, glm::vec3 move_velocity, glm::vec2 rotation_velocity)
    : moveVelocity(move_velocity), rotationVelocity(rotation_velocity), up(0.0f, 1.0f, 0.0f),
      sightDirection(glm::normalize(lookingAt - eye)), viewMatrix(glm::lookAt(eye, lookingAt, up)),
      position(eye)
{
}

void Camera::move(glm::f32 coefficient, MoveDirection direction)
{
    switch(direction)
    {
        case RIGHT: moveRightOrLeft(coefficient); break;
        case LEFT: moveRightOrLeft(-coefficient); break;
        case DOWN: moveDownOrUp(coefficient); break;
        case UP: moveDownOrUp(-coefficient); break;
        case BACKWARD: moveBackwardOrForward(coefficient); break;
        case FORWARD: moveBackwardOrForward(-coefficient); break;
    }
}

void Camera::rotate(glm::f32 coefficient, RotationDirection direction)
{
    switch(direction)
    {
        case ROTATE_UP: rotateUpOrDown(coefficient); break;
        case ROTATE_DOWN: rotateUpOrDown(-coefficient); break;
        case ROTATE_RIGHT: rotateRightOrLeft(coefficient); break;
        case ROTATE_LEFT: rotateRightOrLeft(-coefficient); break;
    }
}

const glm::mat4 &Camera::getViewMatrix() const
{
    return viewMatrix;
}

void Camera::moveRightOrLeft(glm::f32 coefficient)
{
    glm::vec3 translation = coefficient * moveVelocity.x * glm::cross(up, sightDirection);
    translate(translation);
}

void Camera::moveBackwardOrForward(glm::f32 coefficient)
{
    glm::vec3 translation = coefficient * moveVelocity.z * sightDirection;
    translate(translation);
}

void Camera::moveDownOrUp(glm::f32 coefficient)
{
    glm::vec3 translation = coefficient * moveVelocity.y * glm::cross(sightDirection, glm::cross(up, sightDirection));
    translate(translation);
}

void Camera::translate(glm::vec3 translation)
{
    position += translation;
    viewMatrix = glm::translate(viewMatrix, translation);
    viewMatrix = glm::lookAt(position, position + sightDirection, up);
}

#include <iostream>
void Camera::rotateUpOrDown(glm::f32 coefficient)
{
    glm::vec3 old_x_direction = glm::cross(up, sightDirection);
    glm::mat4 rotation_matrix(1);
    rotation_matrix = glm::rotate(rotation_matrix, coefficient*rotationVelocity.y, old_x_direction);
    glm::vec3 new_sight_direction = glm::vec3(rotation_matrix * glm::vec4(sightDirection, 1.0));
    if(glm::dot(old_x_direction, glm::cross(up, new_sight_direction)) <= 0.0f)
    {
        std::cout << "cannot rotate more up/down\n";
        return; // ignore result - do not change camera orientation
    }
    sightDirection = new_sight_direction;
    // viewMatrix = glm::lookAt(
    viewMatrix = rotation_matrix * viewMatrix;
}

void Camera::rotateRightOrLeft(glm::f32 coefficient)
{
    glm::vec3 old_y_direction = glm::cross(sightDirection, glm::cross(up, sightDirection));
    glm::mat4 rotation_matrix(1);
    rotation_matrix = glm::rotate(rotation_matrix, coefficient*rotationVelocity.x, old_y_direction);
    sightDirection = glm::vec3(rotation_matrix * glm::vec4(sightDirection, 1.0));
    viewMatrix = rotation_matrix * viewMatrix;
}