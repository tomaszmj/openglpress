#include <Window.h>
#include <stdexcept>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

Window::Window(const char *title, int width, int height)
    : glfwWindow(glfwCreateWindow(width, height, title, nullptr, nullptr))
{
    if(glfwWindow == nullptr)
        throw std::runtime_error("GLFW window not created");
    glfwMakeContextCurrent(glfwWindow);
    glfwSetWindowUserPointer(glfwWindow, this);
    glfwSetFramebufferSizeCallback(glfwWindow, framebufferSizeCallback);
    glfwSetWindowSize(glfwWindow, width, height);
    framebufferSizeCallback(glfwWindow, width, height);
}

void Window::processInput()
{
    constexpr float camera_move_side_constant = 0.01f;
    constexpr float camera_move_forward_constant = 0.02f;
    constexpr float camera_rotate_constant = 0.05f;

    glfwPollEvents();

    if(glfwGetKey(glfwWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(glfwWindow, true);
    if(glfwGetKey(glfwWindow, GLFW_KEY_UP) == GLFW_PRESS)
    {
        if(glfwGetKey(glfwWindow, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
            camera.rotate(camera_rotate_constant, Camera::ROTATE_UP);
        else
            camera.move(camera_move_side_constant, Camera::UP);
    }
    if(glfwGetKey(glfwWindow, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        if(glfwGetKey(glfwWindow, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
            camera.rotate(camera_rotate_constant, Camera::ROTATE_DOWN);
        else
            camera.move(camera_move_side_constant, Camera::DOWN);
    }
    if(glfwGetKey(glfwWindow, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        if(glfwGetKey(glfwWindow, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
            camera.rotate(camera_rotate_constant, Camera::ROTATE_RIGHT);
        else
            camera.move(camera_move_side_constant, Camera::RIGHT);
    }
    if(glfwGetKey(glfwWindow, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        if(glfwGetKey(glfwWindow, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
            camera.rotate(camera_rotate_constant, Camera::ROTATE_LEFT);
        else
            camera.move(camera_move_side_constant, Camera::LEFT);
    }
    if(glfwGetKey(glfwWindow, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
        camera.move(camera_move_forward_constant, Camera::BACKWARD);
    if(glfwGetKey(glfwWindow, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
        camera.move(camera_move_forward_constant, Camera::FORWARD);
}

bool Window::shouldClose()
{
    return glfwWindowShouldClose(glfwWindow);
}

void Window::swapBuffers()
{
    glfwSwapBuffers(glfwWindow);
}

void Window::clearColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

const glm::mat4 &Window::getTransfromMatrix() const
{
    static glm::mat4 transform;
    transform = projectionMatrix * camera.getViewMatrix();
    return transform;
}

void Window::framebufferSizeCallback(GLFWwindow* glfw_window, int width, int height)
{
    glViewport(0, 0, width, height);
    Window *window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfw_window));
    float width_to_height = static_cast<float>(width)/ static_cast<float>(height);
    window->projectionMatrix = glm::perspective(glm::radians(40.0f), width_to_height, 0.1f, 100.0f);
}
