#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <iostream>
#include <iomanip>

namespace
{
glm::vec3 rotate_vector(const glm::vec3 &vector, glm::f32 angle, const glm::vec3 &axis)
{
    glm::mat4 rotation_matrix(1);
    rotation_matrix = glm::rotate(rotation_matrix, angle, axis);
    return glm::vec3(rotation_matrix * glm::vec4(vector, 1.0));
}
}

Camera::Camera(glm::vec3 eye, glm::vec3 lookingAt)
    : up(0.0f, 1.0f, 0.0f), cameraZ(glm::normalize(eye - lookingAt)),
      position(eye), viewMatrix(glm::lookAt(eye, lookingAt, up))
{
}

void Camera::move(glm::f32 coefficient, MoveDirection direction)
{
    switch(direction)
    {
        case RIGHT: translate(coefficient * cameraX()); break;
        case LEFT: translate(-coefficient * cameraX()); break;
        case UP: translate(coefficient * cameraY()); break;
        case DOWN: translate(-coefficient * cameraY()); break;
        case BACKWARD: translate(coefficient * cameraZ); break;
        case FORWARD: translate(-coefficient * cameraZ); break;
    }
}

void Camera::rotate(glm::f32 coefficient, RotationDirection direction)
{
    switch(direction)
    {
        case ROTATE_UP: rotateUpOrDown(coefficient); break;
        case ROTATE_DOWN: rotateUpOrDown(-coefficient); break;
        case ROTATE_RIGHT: rotateRightOrLeft(-coefficient); break;
        case ROTATE_LEFT: rotateRightOrLeft(coefficient); break;
    }
}

const glm::mat4 &Camera::getViewMatrix() const
{
    return viewMatrix;
}

glm::vec3 Camera::cameraX() const
{
    return glm::cross(up, cameraZ);
}

glm::vec3 Camera::cameraY() const
{
    return glm::cross(cameraZ, cameraX());
}

void printMatrix(const glm::mat4 &matrix)
{
    for(int j = 0; j < 4; ++j)
    {
        for(int i = 0; i < 4; ++i)
            std::cout << std::setw(16) << matrix[i][j];
        std::cout << "\n";
    }
    std::cout << "\n";
}

void Camera::translate(glm::vec3 translation)
{
    position += translation;
    viewMatrix = glm::translate(viewMatrix, -translation);
}

void Camera::rotateUpOrDown(glm::f32 coefficient)
{
    glm::vec3 new_camera_z = rotate_vector(cameraZ, coefficient, cameraX());
    if(!isCameraOrientationCorrect(up, cameraX(), new_camera_z))
    {
        #ifndef NDEBUG
        std::cout << "cannot rotate more up/down\n";
        #endif
        return; // ignore result - do not change camera orientation
    }
    cameraZ = new_camera_z;
    viewMatrix = glm::lookAt(position, position - cameraZ, up);
}

void Camera::rotateRightOrLeft(glm::f32 coefficient)
{
    cameraZ = rotate_vector(cameraZ, coefficient, cameraY());
    viewMatrix = glm::lookAt(position, position - cameraZ, up);
}

bool Camera::isCameraOrientationCorrect(const glm::vec3 &up, const glm::vec3 &camera_x, const glm::vec3 &camera_z)
{
    return glm::dot(camera_x, glm::cross(up, camera_z)) >= 0.0f;
}