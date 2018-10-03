#pragma once
#include <glm/glm.hpp>

class Camera 
{
public:
    enum MoveDirection {RIGHT, LEFT, UP, DOWN, BACKWARD, FORWARD};
    enum RotationDirection {ROTATE_UP, ROTATE_DOWN, ROTATE_RIGHT, ROTATE_LEFT};

    Camera(glm::vec3 eye, glm::vec3 lookingAt,
           glm::vec3 move_velocity = glm::vec3(1.0f, 1.0f, 1.0f),
           glm::vec2 rotation_velocity = glm::vec2(0.01f, 0.01f));
    const glm::mat4 &getViewMatrix() const;
    void move(glm::f32 coefficient, MoveDirection direction);
    void rotate(glm::f32 coefficient, RotationDirection direction);

private:
    glm::vec3 moveVelocity;
    glm::vec2 rotationVelocity;
    const glm::vec3 up;
    glm::vec3 sightDirection;
    glm::mat4 viewMatrix;

    void moveRightOrLeft(glm::f32 coefficient);
    void moveBackwardOrForward(glm::f32 coefficient);
    void moveDownOrUp(glm::f32 coefficient);
    void rotateUpOrDown(glm::f32 coefficient);
    void rotateRightOrLeft(glm::f32 coefficient);
};
