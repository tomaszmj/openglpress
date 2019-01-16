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
#include <CylinderModel.h>
#include <VAOWrapper.h>
#include <RenderedObject.h>
#include <Window.h>

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
        Window window("gkom press", 800, 600);

        glewExperimental = GL_TRUE;
        if(glewInit() != GLEW_OK)
            throw std::runtime_error("GLEW Initialization failed");

        GLint nrAttributes;
        glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
        std::cout << "Max vertex attributes allowed: " << nrAttributes << std::endl;
        glGetIntegerv(GL_MAX_TEXTURE_COORDS, &nrAttributes);
        std::cout << "Max texture coords allowed: " << nrAttributes << std::endl;

        ShaderProgram theProgram("resources/shaders/gl_04.vert", "resources/shaders/gl_04.frag");
        ShaderProgram simpleShader("resources/shaders/gl_simple.vert", "resources/shaders/gl_simple.frag");

        std::unique_ptr<AbstractModelItem> item(dynamic_cast<AbstractModelItem*>(new TexturedCubeModel()));
        std::unique_ptr<AbstractModelItem> item_cylinder(
                    dynamic_cast<AbstractModelItem*>(new CylinderModel(1000, 10)));
        std::unique_ptr<VAOWrapper> vao_wrapper(new VAOWrapper(std::move(item)));
        std::unique_ptr<VAOWrapper> vao_wrapper_cylinder(new VAOWrapper(std::move(item_cylinder)));
        RenderedObject rendered_object(theProgram, std::move(vao_wrapper));
        RenderedObject rendered_object_cylinder(simpleShader, std::move(vao_wrapper_cylinder));

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        Textures textures({
            TextureInitializer("resources/textures/iipw.png", "Texture0"),
            TextureInitializer("resources/textures/weiti.png", "Texture1")
        });
        rendered_object.attachTextures(&textures);

        glEnable(GL_DEPTH_TEST);
        glm::mat4 model(1);
        
        while(!glfwWindowShouldClose(window.getGLFWWindow()))
        {    
            window.processInput();
            glClearColor(0.1f, 0.2f, 0.3f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            textures.bindAll(theProgram.get_programID());

            for(int i = 0; i < 4; ++i)
            {
                glm::mat4 changed_model = glm::translate(model, glm::vec3(i*1.0f, i*1.5f, i*2.0f));
                rendered_object.modelMatrix = changed_model;
                //rendered_object.render(window.getTransfromMatrix());
            }
            rendered_object_cylinder.render(window.getTransfromMatrix());
            glfwSwapBuffers(window.getGLFWWindow());
        }
    }
    catch(std::exception &ex)
    {
        std::cout << ex.what() << std::endl;
        getchar();
    }
    glfwTerminate();

    return 0;
}
