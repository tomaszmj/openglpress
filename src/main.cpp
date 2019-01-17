#include <GL/glew.h>
#include <ShaderProgram.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Textures.h>
#include <TexturedCubeModel.h>
#include <CylinderModel.h>
#include <VAOWrapper.h>
#include <RenderedObject.h>
#include <Window.h>

void run()
{
    Window window("gkom press", 800, 600);

    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK)
        throw std::runtime_error("GLEW Initialization failed");

    ShaderProgram old_program("resources/shaders/gl_04.vert", "resources/shaders/gl_04.frag");
    ShaderProgram simple_shader("resources/shaders/gl_simple.vert", "resources/shaders/gl_simple.frag");
    ShaderProgram background("resources/shaders/gl_04.vert", "resources/shaders/background_wood.frag");

    Textures textures({
        TextureInitializer("resources/textures/iipw.png", "Texture0"),
        TextureInitializer("resources/textures/weiti.png", "Texture1"),
        TextureInitializer("resources/textures/wood.png", "wood"),
    });

    std::unique_ptr<AbstractModelItem> cube(new TexturedCubeModel());
    std::unique_ptr<AbstractModelItem> cylinder(new CylinderModel(1000, 10));
    VAOWrapper vao_wrapper_cube(std::move(cube));
    VAOWrapper vao_wrapper_cylinder(std::move(cylinder));

    glm::mat4 background_model_matrix = glm::scale(glm::mat4(1), glm::vec3(30.0f, 30.0f, 30.0f));
    background_model_matrix = glm::translate(background_model_matrix, glm::vec3(0.0f, 0.5f, 0.0f));

    std::vector<RenderedObject> rendered_objects({
        RenderedObject(old_program, vao_wrapper_cube, glm::translate(glm::mat4(1), glm::vec3(1.5f, 1.5f, 2.0f)), &textures),
        RenderedObject(old_program, vao_wrapper_cube, glm::translate(glm::mat4(1), glm::vec3(2.1f, 3.0f, 4.0f)), &textures),
        RenderedObject(simple_shader, vao_wrapper_cylinder, glm::translate(glm::mat4(1), glm::vec3(0.0f, 0.5f, 0.0f))),
        RenderedObject(background, vao_wrapper_cube, background_model_matrix, &textures),
    });

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glEnable(GL_DEPTH_TEST);

    while(!window.shouldClose())
    {
        window.processInput();
        window.clearColor(0.1f, 0.1f, 0.1f, 0.0f);
        for(const RenderedObject &rendered_object: rendered_objects)
            rendered_object.render(window.getTransfromMatrix());
        window.swapBuffers();
    }
}

int main()
{
    if(glfwInit() != GL_TRUE)
    {
        std::cout << "GLFW initialization failed" << std::endl;
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    try
    {
        run();
    }
    catch(std::exception &ex)
    {
        std::cout << ex.what() << std::endl;
        getchar();
    }
    glfwTerminate();

    return 0;
}
