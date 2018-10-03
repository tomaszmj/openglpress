#pragma once
#include <glm/glm.hpp>

class Camera 
{
public:
    Camera(glm::vec3 eye, glm::vec3 lookingAt);
    const glm::mat4 &getViewMatrix() const;
    void moveRightOrLeft(glm::f32 coefficient);
    void moveForwardOrBackward(glm::f32 coefficient);
    void moveUpOrDown(glm::f32 coefficient);

private:
    glm::mat4 viewMatrix;
    glm::vec3 up;
    glm::vec3 sightDirection;
    glm::vec3 position;
    glm::vec3 moveVelocity;
};
