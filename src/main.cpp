#include <GL/glew.h>
#include <ShaderProgram.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Textures.h>
#include <ColouredCubeModel.h>
#include <SimpleCubeModel.h>
#include <CubeModel.h>
#include <CubeModelInside.h>
#include <CylinderModel.h>
#include <TexturedCylinderModel.h>
#include <VAOWrapper.h>
#include <RenderedObject.h>
#include <Window.h>

void run()
{
    Window window("gkom press", 800, 600);

    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK)
        throw std::runtime_error("GLEW Initialization failed");

    ShaderProgram light_source_shader("resources/shaders/light.vert", "resources/shaders/light_source.frag");
    ShaderProgram metal_shader("resources/shaders/light.vert", "resources/shaders/metal.frag");
    ShaderProgram wood_shader("resources/shaders/light.vert", "resources/shaders/wood.frag");

    Textures textures({
        TextureInitializer("resources/textures/wood.png", "wood"),
        TextureInitializer("resources/textures/metal.png", "metal"),
    });

    VAOWrapper vao_wrapper_simple_cube((SimpleCubeModel()));
    VAOWrapper vao_wrapper_cube((CubeModel()));
    VAOWrapper vao_wrapper_cube_inside((CubeModelInside()));
    VAOWrapper vao_wrapper_cylinder(TexturedCylinderModel(1000, 10));

    glm::mat4 background_model_matrix = glm::scale(glm::mat4(1), glm::vec3(30.0f, 30.0f, 30.0f));
    background_model_matrix = glm::translate(background_model_matrix, glm::vec3(0.0f, 0.5f, 0.0f));

    std::vector<RenderedObject> rendered_objects({
        RenderedObject(metal_shader, vao_wrapper_cube, glm::translate(glm::mat4(1), glm::vec3(1.5f, 1.5f, 2.0f)), &textures),
        RenderedObject(metal_shader, vao_wrapper_cube, glm::translate(glm::mat4(1), glm::vec3(2.1f, 3.0f, 4.0f)), &textures),
        RenderedObject(metal_shader, vao_wrapper_cylinder, glm::translate(glm::mat4(1), glm::vec3(0.0f, 0.5f, 0.0f)), &textures),
        RenderedObject(wood_shader, vao_wrapper_cube_inside, background_model_matrix, &textures),
        RenderedObject(light_source_shader, vao_wrapper_simple_cube, glm::translate(glm::mat4(1), glm::vec3(14.49f, 29.49f, 14.49f))),
    });

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
