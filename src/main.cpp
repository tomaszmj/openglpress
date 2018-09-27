#include <GL/glew.h>
#include <shprogram.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <textures.h>
using namespace std;

GLuint WIDTH = 800, HEIGHT = 600;

void process_input(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
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

        // Let's check what are maximum parameters counts
        GLint nrAttributes;
        glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
        cout << "Max vertex attributes allowed: " << nrAttributes << std::endl;
        glGetIntegerv(GL_MAX_TEXTURE_COORDS, &nrAttributes);
        cout << "Max texture coords allowed: " << nrAttributes << std::endl;

        // Build, compile and link shader program
        ShaderProgram theProgram("resources/shaders/gl_04.vert", "resources/shaders/gl_04.frag");

        // Set up vertex data 
        GLfloat vertices[] =
        {
            0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
            0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,

            0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        };

        GLuint indices[] = {
            0, 1, 2,
            2, 3, 0,
            0, 3, 7,
            7, 4, 0,
            4, 5, 6,
            6, 7, 4,
            5, 1, 2,
            2, 6, 5,
            7, 6, 2,
            2, 3, 7,
            4, 5, 1,
            1, 0, 4
        };

        GLuint VBO, EBO, VAO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // vertex geometry data
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);

        // vertex color data
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);

        // vertex texture coordinates
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
        glEnableVertexAttribArray(2);

        glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

        glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)

                              // Set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // Set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        Textures textures({
            TextureInitializer("resources/textures/iipw.png", "Texture0"),
            TextureInitializer("resources/textures/weiti.png", "Texture1")
        });

        glEnable(GL_DEPTH_TEST);

        glm::mat4 model(1), view, projection, transform;
        model = glm::translate(model, glm::vec3(-0.5f, -0.5f, -0.5f));
        glm::vec3 eye(0.9f, 0.8f, 3.0f);
        glm::vec3 center(0.0f);
        glm::vec3 up(0.0f, 1.0f, 0.0f);
        view = glm::lookAt(eye, center, up);
        
        // main event loop
        while(!glfwWindowShouldClose(window))
        {    
            projection = glm::perspective(glm::radians(40.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
            // view = glm::rotate(view, glm::radians(0.1f), glm::vec3(0, 1, 0));
            transform = projection * view * model;

            // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
            glfwPollEvents();
            process_input(window);

            // Clear the colorbuffer
            glClearColor(0.1f, 0.2f, 0.3f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            textures.bindAll(theProgram.get_programID());

            GLuint transformLoc = glGetUniformLocation(theProgram.get_programID(), "transform");
            glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

            theProgram.Use();

            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);

            // Swap the screen buffers
            glfwSwapBuffers(window);
        }
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }
    catch(exception &ex)
    {
        cout << ex.what() << endl;
        getchar();
    }
    glfwTerminate();

    return 0;
}
