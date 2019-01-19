#pragma once
#include <glm/glm.hpp>

class Camera 
{
public:
    enum MoveDirection {RIGHT, LEFT, UP, DOWN, BACKWARD, FORWARD};
    enum RotationDirection {ROTATE_UP, ROTATE_DOWN, ROTATE_RIGHT, ROTATE_LEFT};

    Camera(glm::vec3 eye=glm::vec3(6.0f, 6.0f, -6.0f), glm::vec3 lookingAt=glm::vec3(0.5f));
    const glm::mat4 &getViewMatrix() const;
    void move(glm::f32 distance, MoveDirection direction);
    void rotate(glm::f32 angle, RotationDirection direction);

private:
    const glm::vec3 up;
    glm::vec3 cameraZ;
    glm::vec3 position;
    glm::mat4 viewMatrix;

    glm::vec3 cameraX() const;
    glm::vec3 cameraY() const;

    void translate(glm::vec3 translation);
    void rotateUpOrDown(glm::f32 angle);
    void rotateRightOrLeft(glm::f32 angle);
    static bool isCameraOrientationCorrect(const glm::vec3 &up, const glm::vec3 &camera_x, const glm::vec3 &camera_z);
};
