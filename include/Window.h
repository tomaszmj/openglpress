#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <Camera.h>

class Window
{
public:
    Window(const char *title, int width, int height);
    double processInputAndGetTimeDiff();
    bool shouldClose();
    void swapBuffers();
    void clearColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
    const glm::mat4 &getTransfromMatrix() const;
    const Camera &getCamera() const;

private:
    GLFWwindow *glfwWindow;
    Camera camera;
    glm::mat4 projectionMatrix;
    double lastEventTime;

    static void framebufferSizeCallback(GLFWwindow *glfw_window, int width, int height);
};
