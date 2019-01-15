#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <Camera.h>

class Window
{
public:
    Window(const char *title, int width, int height);
    void processInput();
    GLFWwindow *getGLFWWindow();
    const glm::mat4 &getTransfromMatrix() const;

private:
    GLFWwindow *glfwWindow;
    Camera camera;
    glm::mat4 projectionMatrix;

    static void framebufferSizeCallback(GLFWwindow *glfw_window, int width, int height);
};
