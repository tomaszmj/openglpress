#include <GL/glew.h>
#include <ShaderProgram.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Textures.h>
#include <SimpleCubeModel.h>
#include <CubeModel.h>
#include <CubeModelInside.h>
#include <CylinderModel.h>
#include <VAOWrapper.h>
#include <RenderedObject.h>
#include <Window.h>
#include <Scene.h>
#include <ModelMatrix.h>
#include <AnimationParameters.h>
#include <Piston.h>
#include <CrushedCylinder.h>

// This program a priori uses only C++11, so std::make_unique may not be supported.
template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

void run()
{
    Window window("gkom press", 800, 600);

    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK)
        throw std::runtime_error("GLEW Initialization failed");

    ShaderProgram light_source_shader("resources/shaders/light_source.vert", "resources/shaders/light_source.frag");
    ShaderProgram metal_shader("resources/shaders/object.vert", "resources/shaders/metal.frag");
    ShaderProgram wood_shader("resources/shaders/object.vert", "resources/shaders/wood.frag");
    ShaderProgram crushing_shader("resources/shaders/crushing.vert", "resources/shaders/metal.frag");

    Textures textures({"resources/textures/wood.png", "resources/textures/metal.png"});

    VAOWrapper vao_wrapper_simple_cube((SimpleCubeModel()));
    VAOWrapper vao_wrapper_cube((CubeModel()));
    VAOWrapper vao_wrapper_cube_inside((CubeModelInside()));
    VAOWrapper vao_wrapper_cylinder(CylinderModel(1000, 10));

    ModelMatrix background, light_source, press_base_cube, press_back, press_top, press_base_cylinder;
    background.setScale(glm::vec3(30.0f, 30.0f, 30.0f));
    background.setTranslation(glm::vec3(0.0f, 14.9999f, 0.0f));
    light_source.setTranslation(glm::vec3(14.49f, 29.49f, 14.49f));
    press_base_cube.setScale(glm::vec3(2.0f, 0.5f, 2.0f));
    press_base_cube.setTranslation(glm::vec3(0.0f, 0.25f, 0.0f));
    press_base_cylinder.setScale(glm::vec3(1.5f, 0.25f, 1.5f));
    press_base_cylinder.setTranslation(glm::vec3(0.0f, 0.625f, 0.0f));
    press_back.setScale(glm::vec3(3.0f, 2.5f, 2.0f));
    press_back.setTranslation(glm::vec3(-2.5f, 1.25f, 0.0f));
    press_top.setScale(glm::vec3(5.0f, 1.5f, 2.0f));
    press_top.setTranslation(glm::vec3(-1.5f, 3.25f, 0.0f));

    AnimationParameters animation_parameters({1, 4, 5, 7}, {1.9, 1.7, 1.2});
    std::unique_ptr<RenderedObject> piston(new Piston(metal_shader, vao_wrapper_cylinder,
         textures[1], glm::vec3(1.0f, 2.0f, 1.0f), animation_parameters));
    std::unique_ptr<RenderedObject> crushed_cylinder(new CrushedCylinder(crushing_shader, vao_wrapper_cylinder,
        textures[1], glm::vec3(0.5f, 0.0f, 0.5f), animation_parameters, 0.75f));

    Scene scene;
    scene.setUpLightSource(glm::vec3(14.49f, 29.49f, 14.49f), glm::vec3(1.0));
    scene.addObject(make_unique<RenderedObject>(light_source_shader, vao_wrapper_simple_cube, light_source, textures[-1]));
    scene.addObject(make_unique<RenderedObject>(wood_shader, vao_wrapper_cube_inside, background, textures[0]));
    scene.addObject(make_unique<RenderedObject>(metal_shader, vao_wrapper_cube, press_base_cube, textures[1]));
    scene.addObject(make_unique<RenderedObject>(metal_shader, vao_wrapper_cube, press_back, textures[1]));
    scene.addObject(make_unique<RenderedObject>(metal_shader, vao_wrapper_cube, press_top, textures[1]));
    scene.addObject(make_unique<RenderedObject>(metal_shader, vao_wrapper_cylinder, press_base_cylinder, textures[1]));
    scene.addObject(std::move(piston));
    scene.addObject(std::move(crushed_cylinder));

    glEnable(GL_DEPTH_TEST);

    while(!window.shouldClose())
    {
        window.processInput();
        scene.update(window);
        window.clearColor(0.1f, 0.1f, 0.1f, 0.0f);
        scene.render(window);
        window.swapBuffers();
    }
}

#ifndef NDEBUG
#include <limits>
void testAnimationParameters()
{
    AnimationParameters p({1,2,3,4}, {10, 5, 4});
    std::cout << p.maxVelocityBeforeCrushing << " " << p.maxVelocityAfterCrushing << std::endl;
    assert(std::fabs(p.calculateY(p.t[0]) - p.h[0]) < std::numeric_limits<double>::epsilon());
    assert(std::fabs(p.calculateY(p.t[1] - 0.00000001) - p.h[1]) < 0.01);
    assert(std::fabs(p.calculateY(p.t[1]) - p.h[1]) < std::numeric_limits<double>::epsilon());
    assert(std::fabs(p.calculateY(p.t[2] - 0.00000001) - p.h[2]) < 0.01);
    assert(std::fabs(p.calculateY(p.t[2]) - p.h[2]) < std::numeric_limits<double>::epsilon());
    assert(std::fabs(p.calculateY(p.t[3]) - p.h[2]) < std::numeric_limits<double>::epsilon());
    assert(std::fabs(p.calculateY(p.t[4] - 0.00000001) - p.h[1]) < 0.01);
    assert(std::fabs(p.calculateY(p.t[4]) - p.h[1]) < std::numeric_limits<double>::epsilon());
    assert(std::fabs(p.calculateY(p.t[5]) - p.h[0]) < std::numeric_limits<double>::epsilon());
//    std::exit(0);
}
#endif

int main()
{
#ifndef NDEBUG
    testAnimationParameters();
#endif
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
