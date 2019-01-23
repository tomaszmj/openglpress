#include <Window.h>
#include <stdexcept>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

Window::Window(const char *title, int width, int height)
    : glfwWindow(glfwCreateWindow(width, height, title, nullptr, nullptr)), lastEventTime(-1.0), lastDeltaTime(0.0)
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
    constexpr double camera_move_side_constant = 1.0;
    constexpr double camera_move_forward_constant = 2.0;
    constexpr double camera_rotate_constant = 0.5;

    if(lastEventTime < 0.0)
        lastEventTime = glfwGetTime();
    glfwPollEvents();
    lastDeltaTime = glfwGetTime() - lastEventTime; // in first function call it will be ~0, then it will work properly
    lastEventTime = glfwGetTime();

    if(glfwGetKey(glfwWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(glfwWindow, true);
    if(glfwGetKey(glfwWindow, GLFW_KEY_UP) == GLFW_PRESS)
    {
        if(glfwGetKey(glfwWindow, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
            camera.rotate(static_cast<float>(camera_rotate_constant * lastDeltaTime), Camera::ROTATE_UP);
        else
            camera.move(static_cast<float>(camera_move_side_constant * lastDeltaTime), Camera::UP);
    }
    if(glfwGetKey(glfwWindow, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        if(glfwGetKey(glfwWindow, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
            camera.rotate(static_cast<float>(camera_rotate_constant * lastDeltaTime), Camera::ROTATE_DOWN);
        else
            camera.move(static_cast<float>(camera_move_side_constant * lastDeltaTime), Camera::DOWN);
    }
    if(glfwGetKey(glfwWindow, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        if(glfwGetKey(glfwWindow, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
            camera.rotate(static_cast<float>(camera_rotate_constant * lastDeltaTime), Camera::ROTATE_RIGHT);
        else
            camera.move(static_cast<float>(camera_move_side_constant * lastDeltaTime), Camera::RIGHT);
    }
    if(glfwGetKey(glfwWindow, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        if(glfwGetKey(glfwWindow, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
            camera.rotate(static_cast<float>(camera_rotate_constant * lastDeltaTime), Camera::ROTATE_LEFT);
        else
            camera.move(static_cast<float>(camera_move_side_constant * lastDeltaTime), Camera::LEFT);
    }
    if(glfwGetKey(glfwWindow, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
        camera.move(static_cast<float>(camera_move_forward_constant * lastDeltaTime), Camera::BACKWARD);
    if(glfwGetKey(glfwWindow, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
        camera.move(static_cast<float>(camera_move_forward_constant * lastDeltaTime), Camera::FORWARD);
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

const Camera &Window::getCamera() const
{
    return camera;
}

double Window::getLastFrameTimeDifference() const
{
    return lastDeltaTime;
}

void Window::framebufferSizeCallback(GLFWwindow* glfw_window, int width, int height)
{
    glViewport(0, 0, width, height);
    Window *window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfw_window));
    float width_to_height = static_cast<float>(width)/ static_cast<float>(height);
    window->projectionMatrix = glm::perspective(glm::radians(40.0f), width_to_height, 0.1f, 100.0f);
}
