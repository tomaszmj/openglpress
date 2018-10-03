#pragma once
#include <glm/glm.hpp>

class Camera 
{
public:
    enum Direction
    {
        RIGHT,
        UP,
        BACKWARD,
        LEFT,
        DOWN,
        FORWARD,
    };

    Camera(glm::vec3 eye, glm::vec3 lookingAt, glm::vec3 move_velocity = glm::vec3(1.0f, 1.0f, 1.0f));
    const glm::mat4 &getViewMatrix() const;
    void move(glm::f32 coefficient, Direction direction);

private:
    glm::vec3 moveVelocity;
    const glm::vec3 up;
    glm::vec3 sightDirection;
    glm::mat4 viewMatrix;

    void moveRightOrLeft(glm::f32 coefficient);
    void moveBackwardOrForward(glm::f32 coefficient);
    void moveUpOrDown(glm::f32 coefficient);
};
