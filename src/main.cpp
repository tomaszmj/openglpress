#include <GL/glew.h>
#include <Shprogram.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
#include <iostream>
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Textures.h>
#include <Camera.h>
#include <TexturedCubeModel.h>
#include <VAOWrapper.h>
#include <RenderTarget.h>
using namespace std;

GLuint WIDTH = 800, HEIGHT = 600;

void process_input(GLFWwindow* window, Camera &camera)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
            camera.rotate(0.01f, Camera::ROTATE_UP);
        else
            camera.move(0.01f, Camera::UP);
    }
    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
            camera.rotate(0.01f, Camera::ROTATE_DOWN);
        else
            camera.move(0.01f, Camera::DOWN);
    }
    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
            camera.rotate(0.01f, Camera::ROTATE_RIGHT);
        else
            camera.move(0.01f, Camera::RIGHT);
    }
    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
            camera.rotate(0.01f, Camera::ROTATE_LEFT);
        else
            camera.move(0.01f, Camera::LEFT);
    }
    if(glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
        camera.move(0.1f, Camera::BACKWARD);
    if(glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
        camera.move(0.1f, Camera::FORWARD);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    cout << "resize: " << width << ", " << height << "\n";
    glViewport(0, 0, width, height);
    WIDTH = width;
    HEIGHT = height;
}

int main()
{
    if(glfwInit() != GL_TRUE)
    {
        cout << "GLFW initialization failed" << endl;
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    try
    {
        GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "GKOM - OpenGL 04", nullptr, nullptr);
        if(window == nullptr)
            throw runtime_error("GLFW window not created");
        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        glewExperimental = GL_TRUE;
        if(glewInit() != GLEW_OK)
            throw runtime_error("GLEW Initialization failed");

        glViewport(0, 0, WIDTH, HEIGHT);

        GLint nrAttributes;
        glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
        cout << "Max vertex attributes allowed: " << nrAttributes << std::endl;
        glGetIntegerv(GL_MAX_TEXTURE_COORDS, &nrAttributes);
        cout << "Max texture coords allowed: " << nrAttributes << std::endl;

        ShaderProgram theProgram("resources/shaders/gl_04.vert", "resources/shaders/gl_04.frag");

        std::unique_ptr<AbstractModelItem> item(dynamic_cast<AbstractModelItem*>(new TexturedCubeModel()));
        std::unique_ptr<VAOWrapper> vao_wrapper(new VAOWrapper(std::move(item)));
        RenderTarget render_target(theProgram, std::move(vao_wrapper));

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        Textures textures({
            TextureInitializer("resources/textures/iipw.png", "Texture0"),
            TextureInitializer("resources/textures/weiti.png", "Texture1")
        });
        render_target.attachTextures(&textures);

        glEnable(GL_DEPTH_TEST);
        glm::mat4 model(1), projection;
        glm::vec3 eye(0.9f, 0.8f, 3.0f);
        glm::vec3 center(0.0f);
        Camera camera(eye, center);
        
        while(!glfwWindowShouldClose(window))
        {    
            projection = glm::perspective(glm::radians(40.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
            glfwPollEvents();
            process_input(window, camera);
            glClearColor(0.1f, 0.2f, 0.3f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            textures.bindAll(theProgram.get_programID());

            for(int i = 0; i < 4; ++i)
            {
                glm::mat4 changed_model = glm::translate(model, glm::vec3(i*1.0f, i*1.5f, i*2.0f));
                render_target.modelMatrix = changed_model;
                render_target.render(projection * camera.getViewMatrix());
            }
            glfwSwapBuffers(window);
        }
    }
    catch(exception &ex)
    {
        cout << ex.what() << endl;
        getchar();
    }
    glfwTerminate();

    return 0;
}
